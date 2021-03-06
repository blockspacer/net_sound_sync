// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PROCESS_H_
#define BASE_PROCESS_H_

#include "base/basictypes.h"
#include "build/build_config.h"

#include <sys/types.h>
#ifdef OS_WIN
#include <windows.h>
#endif

namespace base {

// ProcessHandle is a platform specific type which represents the underlying OS
// handle to a process.
// ProcessId is a number which identifies the process in the OS.
#if defined(OS_WIN)
typedef HANDLE ProcessHandle;
typedef DWORD ProcessId;
typedef HANDLE UserTokenHandle;
const ProcessHandle kNullProcessHandle = NULL;
#elif defined(OS_POSIX)
// On POSIX, our ProcessHandle will just be the PID.
typedef pid_t ProcessHandle;
typedef pid_t ProcessId;
const ProcessHandle kNullProcessHandle = 0;
#endif

#if defined(OS_POSIX) && !defined(OS_MACOSX)
// saved_priority_ will be set to this to indicate that it's not holding
// a valid value. -20 to 19 are valid process priorities.
const int kUnsetProcessPriority = 256;
#endif

class Process {
 public:
  Process() : process_(kNullProcessHandle) {
#if defined(OS_POSIX) && !defined(OS_MACOSX)
    saved_priority_ = kUnsetProcessPriority;
#endif
  }

  explicit Process(ProcessHandle handle) : process_(handle) {
#if defined(OS_POSIX) && !defined(OS_MACOSX)
    saved_priority_ = kUnsetProcessPriority;
#endif
  }

  // A handle to the current process.
  static Process Current();

  // Get/Set the handle for this process. The handle will be 0 if the process
  // is no longer running.
  ProcessHandle handle() const { return process_; }
  void set_handle(ProcessHandle handle) {
    process_ = handle;
#if defined(OS_POSIX) && !defined(OS_MACOSX)
    saved_priority_ = kUnsetProcessPriority;
#endif
  }

  // Get the PID for this process.
  ProcessId pid() const;

  // Is the this process the current process.
  bool is_current() const;

  // Close the process handle. This will not terminate the process.
  void Close();

  // Terminates the process with extreme prejudice. The given result code will
  // be the exit code of the process. If the process has already exited, this
  // will do nothing.
  void Terminate(int result_code);

  // A process is backgrounded when it's priority is lower than normal.
  // Return true if this process is backgrounded, false otherwise.
  bool IsProcessBackgrounded() const;

  // Set a process as backgrounded. If value is true, the priority
  // of the process will be lowered. If value is false, the priority
  // of the process will be made "normal" - equivalent to default
  // process priority.
  // Returns true if the priority was changed, false otherwise.
  bool SetProcessBackgrounded(bool value);

  // Returns an integer representing the priority of a process. The meaning
  // of this value is OS dependent.
  int GetPriority() const;

 private:
  ProcessHandle process_;
#if defined(OS_POSIX) && !defined(OS_MACOSX)
  // Holds the priority that the process was set to when it was backgrounded.
  // If the process wasn't backgrounded it will be kUnsetProcessPriority.
  int saved_priority_;
#endif
};

}  // namespace base

#endif  // BASE_PROCESS_H_
