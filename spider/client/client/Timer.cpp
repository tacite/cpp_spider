#include "Timer.h"

Timer::Timer()
{
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	endCount.QuadPart = 0;
	startTimeInNanoSec = 0;
	endTimeInNanoSec = 0;
}

Timer::~Timer()
{
}


void Timer::start()
{
	startCount.QuadPart = 0;
	endCount.QuadPart = 0;
	startTimeInNanoSec = 0;
	endTimeInNanoSec = 0;
	QueryPerformanceCounter(&startCount);
}

LONGLONG Timer::getElapsedTimeInMicroSec()
{
	QueryPerformanceCounter(&endCount);
	startTimeInNanoSec = startCount.QuadPart;// *(1000000000.0 / frequency.QuadPart);
	endTimeInNanoSec = endCount.QuadPart; // *(1000000000.0 / frequency.QuadPart);
	return endTimeInNanoSec - startTimeInNanoSec;
}

LONGLONG Timer::getElapsedTimeInSec()
{
	return this->getElapsedTimeInMicroSec() / (LONGLONG)1000000.0;
}