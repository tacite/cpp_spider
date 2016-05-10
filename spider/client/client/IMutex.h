#ifndef IMUTEX_H_
#define IMUTEX_H_

class IMutex
{
public:
	virtual ~IMutex() {}
	virtual bool	initialize() = 0;
	virtual bool	lock() = 0;
	virtual void	unlock() = 0;
};

#endif // !IMUTEX_H_
