//
// Copyright (C) 2015 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef UPDATE_ENGINE_CLIENT_LIBRARY_INCLUDE_UPDATE_ENGINE_UPDATE_STATUS_H_
#define UPDATE_ENGINE_CLIENT_LIBRARY_INCLUDE_UPDATE_ENGINE_UPDATE_STATUS_H_

#include <string>

namespace update_engine {

enum class UpdateStatus {
  IDLE = 0,
  CHECKING_FOR_UPDATE,
  UPDATE_AVAILABLE,
  DOWNLOADING,
  VERIFYING,
  FINALIZING,
  UPDATED_NEED_REBOOT,
  REPORTING_ERROR_EVENT,
  ATTEMPTING_ROLLBACK,
  DISABLED,
};

// Enum of bit-wise flags for controlling how updates are attempted.
enum UpdateAttemptFlags : int32_t {
  kNone = 0,
  // Treat the update like a non-interactive update, even when being triggered
  // by the interactive APIs.
  kFlagNonInteractive = (1 << 0),
  // Restrict (disallow) downloading of updates.
  kFlagRestrictDownload = (1 << 1),
};

// These bit-wise operators for the above flags allow for standard bit-wise
// operations to return values in an expected manner, with the need to
// continually cast the results back to UpdateAttemptFlags after the implicit
// conversion to int from enum to perform the bitwise comparison using the
// underlying type.
inline UpdateAttemptFlags operator|(const UpdateAttemptFlags& l,
                                    const UpdateAttemptFlags& r) {
  return static_cast<UpdateAttemptFlags>(static_cast<const int32_t&>(l) |
                                         static_cast<const int32_t&>(r));
}
inline UpdateAttemptFlags operator&(const UpdateAttemptFlags& l,
                                    const UpdateAttemptFlags& r) {
  return static_cast<UpdateAttemptFlags>(static_cast<const int32_t&>(l) &
                                         static_cast<const int32_t&>(r));
}

struct UpdateEngineStatus {
  // When the update_engine last checked for updates (ms since Epoch)
  int64_t last_checked_time_ms;
  // the current status/operation of the update_engine
  UpdateStatus status;
  // the current product version (oem bundle id)
  std::string current_version;
  // the current system version
  std::string current_system_version;
  // The current progress (0.0f-1.0f).
  double progress;
  // the size of the update (bytes)
  uint64_t new_size_bytes;
  // the new product version
  std::string new_version;
  // the new system version, if there is one (empty, otherwise)
  std::string new_system_version;
};

}  // namespace update_engine

#endif  // UPDATE_ENGINE_CLIENT_LIBRARY_INCLUDE_UPDATE_ENGINE_UPDATE_STATUS_H_
