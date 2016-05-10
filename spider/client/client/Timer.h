#ifndef TIMER_H_
# define TIMER_H_

#include <windows.h>

class Timer
{
public:
	Timer();
	~Timer();
	void   start();
	LONGLONG getElapsedTimeInSec();
	LONGLONG getElapsedTimeInMicroSec();

private:
	LONGLONG startTimeInNanoSec;
	LONGLONG endTimeInNanoSec;
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
};

#endif /* TIMER_H_ */