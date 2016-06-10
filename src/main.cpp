#include <signal.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "src/args.hpp"
#include "src/slower.hpp"

using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::cin;
using std::cout;
using std::endl;
using std::stoul;
using std::this_thread::sleep_until;

static bool running = true;

static void stopRunning(int signum) {
	running = false;
}

int main(int _argc, char **_argv) {
	time_point<steady_clock> wakeup_point;
	milliseconds up, down;
	int pid;

	argc = _argc;
	argv = _argv;

	wakeup_point = steady_clock::now();
	up = milliseconds(10);
	down = milliseconds(10);

	switch (argc) {
	case 4:
		down = milliseconds(stoul(argv[3]));
	case 3:
		up = milliseconds(stoul(argv[2]));
	case 2:
		pid = stoul(argv[1]);
		break;
	default:
		cout << "usage: " << argv[0]
		     << " <pid> [<up duration>] [<down duration>]"
		     << endl;
		cout << "Stops and continues a process repeatedly."
		     << endl;
		cout << "Times measured in miliseconds and rounded to an int."
		     << endl;
		cout << "Times default to 10 milliseconds each if unspecified."
		     << endl;
		return 0;
	}

	std::unique_ptr<Slower> slower = makeUnixSlower(pid);

	signal(SIGINT, stopRunning);
	signal(SIGQUIT, stopRunning);

	while (running) {
		wakeup_point += up;
		sleep_until(wakeup_point);
		slower->pause();

		wakeup_point += down;
		sleep_until(wakeup_point);
		slower->resume();
	}
	return 0;
}
