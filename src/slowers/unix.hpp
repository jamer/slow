#ifndef SRC_SLOWERS_UNIX_HPP_
#define SRC_SLOWERS_UNIX_HPP_

#include <signal.h>
#include <stdio.h>

#include "src/slower.hpp"

class UnixSlower : public Slower {
 public:
	UnixSlower(int pid);
	~UnixSlower() = default;
	void _pause();
	void _resume();

 private:
	pid_t pid;
};

#endif  // SRC_SLOWERS_UNIX_HPP_
