#ifndef SRC_SLOWERS_MACH_HPP_
#define SRC_SLOWERS_MACH_HPP_

#include <mach/mach_init.h>
#include <mach/mach_port.h>
#include <mach/task.h>
#include <mach/task_info.h>
#include <mach/thread_act.h>
#include <mach/vm_map.h>

#include "src/slower.hpp"

class MachSlower : public Slower {
 public:
	MachSlower(int pid);
	~MachSlower() = default;
	void _pause();
	void _resume();

 private:
	task_t task;
};

#endif  // SRC_SLOWERS_MACH_HPP_
