#include <stdio.h>
#include <stdlib.h>

#include "src/slowers/unix.hpp"

UnixSlower::UnixSlower(int pid) : Slower(pid), pid(pid) {
	if (kill(pid, 0)) {
		perror("kill");
		exit(1);
	}
}

void UnixSlower::_pause() {
	if (kill(pid, SIGSTOP)) {
		perror("kill");
		exit(1);
	}
}

void UnixSlower::_resume() {
	if (kill(pid, SIGCONT)) {
		perror("kill");
		exit(1);
	}
}

std::unique_ptr<Slower> makeUnixSlower(int pid) {
	return std::make_unique<UnixSlower>(pid);
}
