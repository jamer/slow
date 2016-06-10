#include <stdio.h>
#include <stdlib.h>

#include "src/args.hpp"
#include "src/slowers/mach.hpp"

static const char *machErrorStrings[] {
	[KERN_SUCCESS] = "KERN_SUCCESS",
	[KERN_PROTECTION_FAILURE] = "KERN_PROTECTION_FAILURE",
	[KERN_INVALID_ARGUMENT] = "KERN_INVALID_ARGUMENT",
	[KERN_FAILURE] = "KERN_FAILURE",
	[KERN_ABORTED] = "KERN_ABORTED",
	[KERN_RETURN_MAX] = nullptr
};

static void machError(const char *funcName, kern_return_t err) {
	printf("%s: %s: %s\n",
		argv[0],
		funcName,
		machErrorStrings[err] ? machErrorStrings[err] : "unknown");
}

MachSlower::MachSlower(int pid) : Slower(pid) {
	kern_return_t err = task_for_pid(mach_task_self(), pid, &task);
	if (err != KERN_SUCCESS) {
		machError("task_for_pid", err);
		exit(1);
	}
}

void MachSlower::_pause() {
	kern_return_t err = task_suspend(task);
	if (err != KERN_SUCCESS) {
		machError("task_suspend", err);
		exit(1);
	}
}

void MachSlower::_resume() {
	kern_return_t err = task_resume(task);
	if (err != KERN_SUCCESS) {
		machError("task_resume", err);
		exit(1);
	}
}

std::unique_ptr<Slower> makeMachSlower(int pid) {
	return std::make_unique<MachSlower>(pid);
}
