#include "WMutex.h"
#include <iostream>

WMutex::WMutex()
{

}

WMutex::~WMutex()
{
	CloseHandle(ghMutex);
}

 bool	WMutex::initialize()
{
	ghMutex = CreateMutex(NULL, FALSE, NULL);
	if (ghMutex == NULL)
	{
		std::cerr << "Error while creating mutex" << std::endl;
		return false;
	}
	return true;
}

 bool	WMutex::lock()
{
	DWORD dwWaitResult = WaitForSingleObject(
		ghMutex,    // handle to mutex
		INFINITE);  // no time-out interval

	switch (dwWaitResult)
	{
		case WAIT_OBJECT_0:
			return true;
		default:
			return false;
	}
	return false;
}

 void	WMutex::unlock()
{
	if (!ReleaseMutex(ghMutex))
	{
		// Handle error.
	}
}