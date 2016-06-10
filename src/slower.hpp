#ifndef SRC_SLOWER_HPP_
#define SRC_SLOWER_HPP_

#include <memory>

class Slower {
 public:
	Slower(int pid);
	virtual ~Slower();
	void pause();
	void resume();

 private:
	virtual void _pause() = 0;
	virtual void _resume() = 0;

	bool paused;
};

std::unique_ptr<Slower> makeMachSlower(int pid);
std::unique_ptr<Slower> makeUnixSlower(int pid);

#endif  // SRC_SLOWER_HPP_
