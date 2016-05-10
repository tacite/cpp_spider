#ifndef		ITHREAD_H_
# define	ITHREAD_H_

class		IThread
{
public:
	virtual ~IThread() {}
	virtual unsigned int initialize(void *(*)(void *), void*) = 0;
	virtual bool join() = 0;
	virtual bool wait(unsigned int) = 0;
	virtual bool destroy(unsigned int) = 0;
	virtual bool destroyAll() = 0;
};

#endif /* ITHREAD_H_ */