#
# Copyright (c) 2020-2021 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
"""Configuration assembly algorithm."""
import itertools

from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, List, Optional, Set

from setuptools.build_meta import build_editable

from mbed_tools.project import MbedProgram
from mbed_tools.build._internal.config.config import Config
from mbed_tools.build._internal.config import source
from mbed_tools.build._internal.find_files import LabelFilter, RequiresFilter, filter_files, find_files


def assemble_config(target_attributes: dict, program: MbedProgram) -> Config:
    """Assemble config for given target and program directory.

    Mbed library and application specific config parameters are parsed from mbed_lib.json and mbed_app.json files
    located in the project source tree.
    The config files contain sets of "labels" which correspond to directory names in the mbed-os source tree. These
    labels are used to determine which mbed_lib.json files to include in the final configuration.

    The mbed_app.json config overrides must be applied after all the mbed_lib.json files have been parsed.
    Unfortunately, mbed_app.json may also contain filter labels to tell us which mbed libs we're depending on.
    This means we have to collect the filter labels from mbed_app.json before parsing any other config files.
    Then we parse all the required mbed_lib config and finally apply the app overrides.

    Args:
        target_attributes: Mapping of target specific config parameters.
        program: MbedProgram to build the config for
    """
    mbed_lib_files: Set[Path] = set()

    for path in [program.root, program.mbed_os.root]:
        mbed_lib_files.update(find_files("mbed_lib.json", path.absolute().resolve()))
        mbed_lib_files.update(find_files("mbed_lib.json5", path.absolute().resolve()))

    config = _assemble_config_from_sources(target_attributes, list(mbed_lib_files), program.files.app_config_file)

    # Set up the config source path list using the path to every JSON
    config.json_sources.extend(mbed_lib_files)
    if program.files.app_config_file is not None:
        config.json_sources.append(program.files.app_config_file)
    config.json_sources.append(program.mbed_os.targets_json_file)
    config.json_sources.append(program.mbed_os.cmsis_mcu_descriptions_json_file)
    if program.files.custom_targets_json.exists():
        config.json_sources.append(program.files.custom_targets_json)

    # Make all JSON sources relative paths to the program root
    def make_relative_if_possible(path: Path):
        # Sadly, Pathlib did not gain a better way to do this until newer python versions.
        try:
            return path.relative_to(program.root)
        except ValueError:
            return path

    config.json_sources = [make_relative_if_possible(json_source) for json_source in config.json_sources]

    return config


def _assemble_config_from_sources(
    target_attributes: dict, mbed_lib_files: List[Path], mbed_app_file: Optional[Path] = None
) -> Config:
    config = Config(source.prepare(target_attributes, source_name="target"))
    previous_filter_data = None
    app_data = None
    if mbed_app_file:
        # We need to obtain the file filter data from mbed_app.json so we can select the correct set of mbed_lib.json
        # files to include in the config. We don't want to update the config object with all of the app settings yet
        # as we won't be able to apply overrides correctly until all relevant mbed_lib.json files have been parsed.
        app_data = source.from_file(
            mbed_app_file, default_name="app", target_filters=FileFilterData.from_config(config).labels
        )
        _get_app_filter_labels(app_data, config)

    current_filter_data = FileFilterData.from_config(config)
    while previous_filter_data != current_filter_data:
        filtered_files = _filter_files(mbed_lib_files, current_filter_data)
        for config_file in filtered_files:
            config.update(source.from_file(config_file, target_filters=current_filter_data.labels))
            # Remove any mbed_lib files we've already visited from the list so we don't parse them multiple times.
            mbed_lib_files.remove(config_file)

        previous_filter_data = current_filter_data
        current_filter_data = FileFilterData.from_config(config)

    # Apply mbed_app.json data last so config parameters are overriden in the correct order.
    if app_data:
        config.update(app_data)

    return config


def _get_app_filter_labels(mbed_app_data: dict, config: Config) -> None:
    requires = mbed_app_data.get("requires")
    if requires:
        config["requires"] = requires

    config.update(_get_file_filter_overrides(mbed_app_data))


def _get_file_filter_overrides(mbed_app_data: dict) -> dict:
    return {"overrides": [override for override in mbed_app_data.get("overrides", []) if override.modifier]}


@dataclass(frozen=True)
class FileFilterData:
    """Data used to navigate mbed-os directories for config files."""

    labels: Set[str]
    features: Set[str]
    components: Set[str]
    requires: Set[str]

    @classmethod
    def from_config(cls, config: Config) -> "FileFilterData":
        """Extract file filters from a Config object."""
        return cls(
            labels=config.get("labels", set()) | config.get("extra_labels", set()),
            features=set(config.get("features", set())),
            components=set(config.get("components", set())),
            requires=set(config.get("requires", set())),
        )


def _filter_files(files: Iterable[Path], filter_data: FileFilterData) -> Iterable[Path]:
    filters = (
        LabelFilter("TARGET", filter_data.labels),
        LabelFilter("FEATURE", filter_data.features),
        LabelFilter("COMPONENT", filter_data.components),
        RequiresFilter(filter_data.requires),
    )
    return filter_files(files, filters)
