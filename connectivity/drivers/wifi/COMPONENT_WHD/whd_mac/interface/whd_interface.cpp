/*
 * Copyright (c) 2018-2019, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "WhdSTAInterface.h"
#include "WhdSoftAPInterface.h"
#include "whd_interface.h"

whd_interface_shared_info_t whd_iface_shared;

WiFiInterface *WiFiInterface::get_target_default_instance()
{
    static WhdSTAInterface wifi;
    return &wifi;
}

WhdSoftAPInterface *WhdSoftAPInterface::get_default_instance()
{
    static WhdSoftAPInterface softap;
    return &softap;
}

/*
 * With e.g. GCC linker option "--undefined=<LINK_FOO>", pull in this
 * object file anyway for being able to override weak symbol successfully
 * even though from static library. See:
 * https://stackoverflow.com/questions/42588983/what-does-the-gnu-ld-undefined-option-do
 *
 * NOTE: For C++ name mangling, 'extern "C"' is necessary to match the
 *       <LINK_FOO> symbol correctly.
 */
extern "C"
void LINK_WHD_INTERFACE_CPP(void)
{
}
