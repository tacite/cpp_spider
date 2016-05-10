#ifndef		WTHREAD_H_
# define	WTHREAD_H_

#include	"IThread.h"
#include	<Windows.h>
//#include	<tchar.h>
//#include	<strsafe.h>
#define		MAX_THREAD 255


class		WThread : public IThread
{
private:
	unsigned int maxIdThread;
	unsigned int nbThread;
	void * pDataArray[MAX_THREAD];
	DWORD   dwThreadIdArray[MAX_THREAD];
	HANDLE  hThreadArray[MAX_THREAD];
public:
	WThread();
	virtual ~WThread();

	virtual unsigned int initialize(void * (*)(void*), void *);
	virtual bool join();
	virtual bool destroy(unsigned int);
	virtual bool wait(unsigned int);
	virtual bool destroyAll();
};

#endif		/* WTHREAD_H_ */
