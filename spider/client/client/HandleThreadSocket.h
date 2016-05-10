#ifndef HANDLETHREADSOCKET_H_
#	define HANDLETHREADSOCKET_H_

#include <string>
#include <algorithm>
#include <functional>
#include <map>

#include "Core.h"
#include "IMutex.h"
#include <windows.h>

class IThread;

typedef struct
{
	char * data;
	Core   * core;
	unsigned int size;
	IMutex *m;
	bool result;
}		mData;


class HandleThreadSocket
{
public:
	HandleThreadSocket(Core *);
	~HandleThreadSocket();
	
	/* Function static for thread */
	static void * send(void *);
	static void * receive(void *);
	static void * connect(void *);


	bool sendData(char *, unsigned int);
	void receiveData();
	bool connectSocket(std::string &, unsigned int);

	unsigned int getNbThreadRecv();
	void decNbThreadRecv();

private:
	unsigned int start(int, void *);

	IThread  * t;
	Core * _c;
	IMutex * _m;

	std::string  ip;
	unsigned int port;

	unsigned int nb_thread_recv;

	std::map<unsigned int, char *> data;
	unsigned int size;
	bool result;
};

#endif // !HANDLETHREADSOCKET_H_
