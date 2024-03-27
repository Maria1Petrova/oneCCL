/*
 Copyright 2016-2020 Intel Corporation
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
     http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#pragma once

#include "oneapi/ccl/config.h"

/*
 * This file uses local .clang-format file in order to have
 * unlimited line length which is required for proper
 * handling in doxygen.
*/

#ifdef CCL_ENABLE_SYCL

/**
 * @brief Experimental OneCCL Environment Variables
 * Functionality of these variables has not been (fully)
 * tested and, therefore, cannot be supported nor guaranteed.
 *
 * @defgroup ExpOneCCLvars Experimental OneCCL Environment Variables
 * @{
 * @}
 **/

/**
 * @addtogroup ExpOneCCLvars
 * @{
 */

/**
 * @brief Set to specify monolithic pipeline approach for
 * reduce_scatter phase in allreduceand reduce collectives.
 * 
 * @details This enviroment variable has the advantage of forming a seamless
 * pipeline that conceals the data transfer time across MDFI. This way,
 * a process reads the data from its peer tile on the same GPU, performs
 * the reduction, and writes to a temporary buffer located on a different
 * GPU. This modification will cover the time for transferring
 * the data through XeLinks during the reduce-scatter phase in allreduce
 * and reduce collectives.
 * 
 * "<value>" :  "0", "1"
 * 
 * By-default: "1"
 */
constexpr const char* CCL_REDUCE_SCATTER_MONOLITHIC_PIPELINE_KERNEL = "CCL_REDUCE_SCATTER_MONOLITHIC_PIPELINE_KERNEL";

/**
 * @brief Set to specify the mechanism to use for Level Zero IPC exchange
 * 
 * @details \n "drmfd" - Uses a the DRM mechanism for Level Zero IPC exchange.
 * This is an experimental mechanism that is used with OS kernels previous
 * to SP4. To use the DRM mechanism, the libdrm and drm headers must be available
 * on a system. \n "pidfd" - Uses pidfd mechanism for Level Zero IPC exchange.
 * It requires OS kernel SP4 or above as it requires Linux 5.6 kernel or above \n 
 * "sockets" - Uses socket mechanism for Level Zero IPC exchange. It is usually
 * slower than the other two mechanisms, but can be used for debugging as
 * it is usually available on most systems
 * 
 * "<value>": "drmfd", "pidfd", "sockets"
 * 
 * By-default: "drmfd"
 */
constexpr const char* CCL_ZE_IPC_EXCHANGE = "CCL_ZE_IPC_EXCHANGE";

/**
 * @brief Use bdf support for mapping logical to physical devices
 *
 * @details To obtain the physical device id based on the bdf,
 * we need get and then parse the bdf values. Then using those
 * values we can identify the particular device by referencing
 * the appropriate fields in a pci configuration space for
 * pci devices.to utilize bdf for the purpose of mapping logical
 * devices to their corresponding physical devices.
 *
 * "<value>" :  "0", "1"
 *
 * By-default: "1"
 */
constexpr const char* CCL_ZE_DRM_BDF_SUPPORT = "CCL_ZE_DRM_BDF_SUPPORT";

/**
 * @brief Use the fallback algorithm for reduce_scatter
 *
 * @details The fallback algorithm performs a full allreduce and
 * then copies a subset of its output to the recv buffer.
 * Currently, the fallback algorithm is used for scaleout whereas
 * scaleup uses optimized algorithm.
 *
 * "<value>" :  "0", "1"
 *
 * By-default: "0"
 */
constexpr const char* CCL_REDUCE_SCATTER_FALLBACK_ALGO = "CCL_REDUCE_SCATTER_FALLBACK_ALGO";

/**
 * @brief Automatically tune algorithm protocols based on port count
 *
 * @details Use number of ports to detect the 12 ports system and
 * use write protocols on such systems for collectives. Users can
 * disable this automatic detection and select the protocols manually.
 *
 * "<value>" :  "0", "1"
 *
 * By-default: "1"
 */
constexpr const char* CCL_ZE_AUTO_TUNE_PORTS = "CCL_ZE_AUTO_TUNE_PORTS";

/**
 * @brief Enable switching of read and write protocols for pt2pt topo algorithm
 *
 * @details Control pt2pt read/write protocols.\n Read Protocol:\n
 * It means SEND side is exchanging the handle with RECV side.
 * Then execute the copy operation on the RECV operation side, where the dst buf
 * is the local buffer and the source buffer is the remote buffer.\n
 *
 * Write Protocol:\n
 * it means RECV side is exchanging the handle with SEND side.
 * Execute the copy operation on the SEND operation side, where the dst buf is the
 * remote buffer and the source buffer is the local buffer.
 *\n
 * "<value>" :  "0", "1"
 *\n
 * By-default: "1"
 */
constexpr const char* CCL_ZE_PT2PT_READ = "CCL_ZE_PT2PT_READ";

/**
 * @brief Tunable value for collectives to adjust copy engine indexes
 *
 * @details use 2,4,6 copy engine indexes for host with 6 ports
 * for allreduce, reduce and allgatherv
 * "<value>":
 * "on" - always use write mode with calculated indexes
 * "off" - always disabled
 * "detected" - determined by the logic in detection
 * "undetected" - the default value, used before the logic in
 * detection
 *
 * By-default: "undetected"
 */
constexpr const char* CCL_ZE_TYPE2_TUNE_PORTS = "CCL_ZE_TYPE2_TUNE_PORTS";

/**
 * @brief Switch ccl::barrier() host-sync / host-async options
 *
 * @details Historically ccl::barrier() was always synchronous.
 * That does not match with oneCCL asynchronous concept. Same as other
 * collectives, ccl::barrier() should be host-asynchronous if possible.
 * As it would be too much to change in one moment, we start through
 * experimental variable which introduces the option to make barrier
 * host-asynchronous. Use CCL_BARRIER_SYNC=0 to achieve that.
 *
 * By-default: "1 (SYNC)"
 */
constexpr const char* CCL_BARRIER_SYNC = "CCL_BARRIER_SYNC";
/** @} */
/** @} */

constexpr const char* CCL_ALLREDUCE_USE_TMP_BUF = "CCL_ALLREDUCE_USE_TMP_BUF";
constexpr const char* CCL_ALLREDUCE_SMALL_SIZE_THRESHOLD = "CCL_ALLREDUCE_SMALL_SIZE_THRESHOLD";
constexpr const char* CCL_ALLREDUCE_MEDIUM_SIZE_THRESHOLD = "CCL_ALLREDUCE_MEDIUM_SIZE_THRESHOLD";

constexpr const char* CCL_REDUCE_SCATTER_USE_TMP_BUF = "CCL_REDUCE_SCATTER_USE_TMP_BUF";
constexpr const char* CCL_REDUCE_SCATTER_SMALL_SIZE_THRESHOLD = "CCL_REDUCE_SCATTER_SMALL_SIZE_THRESHOLD";
constexpr const char* CCL_REDUCE_SCATTER_MEDIUM_SIZE_THRESHOLD = "CCL_REDUCE_SCATTER_MEDIUM_SIZE_THRESHOLD";

constexpr const char* CCL_ALLGATHERV_USE_TMP_BUF = "CCL_ALLGATHERV_USE_TMP_BUF";
constexpr const char* CCL_ALLGATHERV_CHUNK_SIZE = "CCL_ALLGATHERV_CHUNK_SIZE";
constexpr const char* CCL_ALLGATHERV_SMALL_SIZE_THRESHOLD = "CCL_ALLGATHERV_SMALL_SIZE_THRESHOLD";
constexpr const char* CCL_ALLGATHERV_MEDIUM_SIZE_THRESHOLD = "CCL_ALLGATHERV_MEDIUM_SIZE_THRESHOLD";

constexpr const char* CCL_SKIP_SCHEDULER = "CCL_SKIP_SCHEDULER";
constexpr const char* CCL_USE_CCL_BARRIER = "CCL_USE_CCL_BARRIER";
constexpr const char* CCL_USE_SYCL_BARRIER = "CCL_USE_SYCL_BARRIER";

#endif // CCL_ENABLE_SYCL
