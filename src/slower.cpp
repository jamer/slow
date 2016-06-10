#include "src/slower.hpp"

Slower::Slower(int pid) : paused(false) { };

Slower::~Slower() {
	if (paused) {
		resume();
	}
}

void Slower::pause() {
	paused = true;
	_pause();
}

void Slower::resume() {
	_resume();
	paused = false;
}
