# BUILD ERROR
[build] [133/133 100% :: 6.720] Linking CXX executable main.elf
[build] FAILED: main.elf 
[build] C:\Windows\system32\cmd.exe /C "cd . && C:\ST\STM32CubeCLT\GNU-tools-for-STM32\bin\arm-none-eabi-g++.exe -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fmessage-length=0 -fno-exceptions -ffunction-sections -fdata-sections -funsigned-char -fomit-frame-pointer -g3 -mthumb -mcpu=cortex-m0 -Wno-register -Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -Wl,--end-group -specs=nosys.specs -Wl,--cref    -T C:/MbedCE/MbedCE_H5_NEw/build/mbed-lpc11u24-401.link_script.ld -Wl,-Map=C:/MbedCE/MbedCE_H5_NEw/build/main.elf.map -Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_memalign_r -Wl,--wrap,_calloc_r -Wl,--wrap,exit -Wl,--wrap,atexit -Wl,-n @CMakeFiles\main.rsp -o main.elf  && C:\Windows\system32\cmd.exe /C "cd /D C:\MbedCE\MbedCE_H5_NEw\build && arm-none-eabi-objcopy -O binary C:/MbedCE/MbedCE_H5_NEw/build/main.elf C:/MbedCE/MbedCE_H5_NEw/build/main.bin && "C:\Program Files\CMake\bin\cmake.exe" -E echo "-- built: C:/MbedCE/MbedCE_H5_NEw/build/main.bin" && arm-none-eabi-objcopy -O ihex C:/MbedCE/MbedCE_H5_NEw/build/main.elf C:/MbedCE/MbedCE_H5_NEw/build/main.hex && "C:\Program Files\CMake\bin\cmake.exe" -E echo "-- built: C:/MbedCE/MbedCE_H5_NEw/build/main.hex" && cd /D C:\MbedCE\MbedCE_H5_NEw\mbed-os\tools\python && C:\MbedCE\MbedCE_H5_NEw\mbed-os\venv\Scripts\python.exe -m memap.memap -t GCC_ARM C:/MbedCE/MbedCE_H5_NEw/build/main.elf.map --depth 2""
[build] C:/ST/STM32CubeCLT/GNU-tools-for-STM32/bin/../lib/gcc/arm-none-eabi/11.3.1/../../../../arm-none-eabi/bin/ld.exe:C:/MbedCE/MbedCE_H5_NEw/build/mbed-lpc11u24-401.link_script.ld:78 cannot move location counter backwards (from 00000000100026e8 to 0000000010001c00)
[build] collect2.exe: error: ld returned 1 exit status
[build] ninja: build stopped: subcommand failed.
[proc] The command: "C:\Program Files\CMake\bin\cmake.EXE" --build c:/MbedCE/MbedCE_H5_NEw/build --config Debug --target main -- exited with code: 1
[driver] Build completed: 00:00:06.757
[build] Build finished with exit code 1



[![Mbed OS][mbed-os-logo]][mbed-os-link]
# Mbed OS Community Edition

[![Build status master][mbed-master-svg]][mbed-master]

[mbed-os-logo]: logo.png
[mbed-os-link]: https://www.mbed.com/en/platform/mbed-os/
[mbed-master]: https://github.com/multiplemonomials/mbed-os/actions/workflows/basic_checks.yml
[mbed-master-svg]: https://github.com/multiplemonomials/mbed-os/actions/workflows/basic_checks.yml/badge.svg

Arm Mbed OS is an open source embedded operating system designed specifically for the "things" in the Internet of Things. It includes all the features you need to develop a connected product based on an Arm Cortex-M microcontroller, including security, connectivity, an RTOS and drivers for sensors and I/O devices.

Mbed OS provides a platform that includes:

- Security foundations.
- Cloud management services.
- Drivers for sensors, I/O devices and connectivity.

This is Mbed OS Community Edition (CE), a fork focused on improving the build system and tooling, fixing bugs, and keeping maintenance going after ARM's step back from the Mbed project.

## License and contributions

The software is provided under the [Apache-2.0 license](LICENSE-apache-2.0.txt). Contributions to this project are accepted under the same license. Please see [contributing.md](CONTRIBUTING.md) for more information.

This project contains code from other projects. The original license text is included in those source files. They must comply with our [license guide](https://os.mbed.com/docs/mbed-os/latest/contributing/license.html).

Folders containing files under different permissive license than Apache 2.0 are listed in the [LICENSE](LICENSE.md) file.

## Getting started for developers

To start a new project that uses Mbed CE, see the setup guide [here](https://github.com/mbed-ce/mbed-os/wiki/New-Project-Setup-Guide).

We have a [developer website](https://os.mbed.com) for asking questions, engaging with others, finding information on boards and components, using an online IDE and compiler, reading the documentation and learning about what's new and what's coming next in Mbed OS.

Additionally, the [discussions page](https://github.com/mbed-ce/mbed-os/discussions) on this repo can be used for proposing and discussing specific code changes.

## Documentation

### Mbed CE Docs
For the Mbed CE code-level documentation (Doxygen), see [here](https://mbed-ce.github.io/mbed-os/group__mbed-os-public.html).  For an auto-generated listing of target boards supported by Mbed, and the drivers & features each target supports, see the [targets index here](https://mbed-ce.github.io/mbed-ce-test-tools/targets/) and the [drivers index here](https://mbed-ce.github.io/mbed-ce-test-tools/drivers/).

Mbed CE is still working on more complete documentation infrastructure. Eventually, we hope to migrate all of the docs and examples as well.  However, for now, see below to access those on the original Mbed OS docs site.

### Original ARM Mbed OS Docs
For more information about Mbed OS, please see [the published Mbed OS documentation](https://os.mbed.com/docs/latest). It includes general overview information, step-by-step tutorials, porting information and background reference materials about our architecture and tools.



