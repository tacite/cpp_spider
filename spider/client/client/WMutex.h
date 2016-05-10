#ifndef WMUTEX_H_
#define WMUTEX_H

#include "IMutex.h"
#include <windows.h>

class WMutex : public IMutex
{
private:	
	HANDLE ghMutex;
public:
	WMutex();
	virtual ~WMutex();
	virtual bool	initialize();
	virtual bool	lock();
	virtual void	unlock();
};

#endif // !WMUTEX_H_