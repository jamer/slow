#include <chrono>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <thread>

using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::cin;
using std::cout;
using std::endl;
using std::stoul;
using std::this_thread::sleep_until;

static pid_t pid;

static void resume(int signum)
{
	kill(pid, SIGCONT);
	exit(1);
}

int main(int argc, char *argv[])
{
	time_point<steady_clock> wakeup_point;
	milliseconds up, down;

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

	if (kill(pid, 0)) {
		perror("kill");
		return 1;
	}

	signal(SIGINT, resume);
	signal(SIGQUIT, resume);

	while (true) {
		wakeup_point += up;
		sleep_until(wakeup_point);
		if (kill(pid, SIGSTOP)) {
			perror("kill");
			return 1;
		}

		wakeup_point += down;
		sleep_until(wakeup_point);
		if (kill(pid, SIGCONT)) {
			perror("kill");
			return 1;
		}
	}
	return 0;
}
