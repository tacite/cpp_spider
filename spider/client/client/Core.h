#ifndef __CORE_H__
# define __CORE_H__
# define IP "127.0.0.1"
# define PORT 4242

# define CLIENT_DISCONNECT 0
# define CLIENT_WAIT_FOR_CONNECT 1
# define CLIENT_CONNECTED 2// With Socket
# define CLIENT_SENDED_CMD 3 // have send cmd for connection protocol
# define CLIENT_PROTOCOL_OK 4 // is connected with protocol

#include <exception>
#include <string>
#include <sstream>
#include <iostream>

#include "Command.h"
#include "Timer.h"

class FileLog;
class IMutex;
class HandleThreadSocket;
class ISocketHandler;

class Core {
private:
	FileLog *file;
	Command cmd;
	Timer time;
	HandleThreadSocket * h;
	ISocketHandler * socket;
	IMutex * mutex;

	unsigned int port;
	std::string ip;

	/*bool _isConnected;
	bool _isOffline;
	bool _isTryingConnect;
	bool _isTryingProtocolConnect;*/

	int step;

	double timeout;
	std::vector<char *> _toSend;
	std::vector<char *> _recv;

public:
	
	Core(const std::string & _ip, unsigned int _port);
	~Core();

	bool initialize(void);
	bool loop(void);
	
	bool tryConnect();
	bool getReturn();
	bool SendFile();
	bool SendCommand();

	/* getter */
	ISocketHandler * getSocket() const;
	Command & getCommand();
	int getState();
	char * getResponse();

	// setter 
	void setState(int);
	void addResponse(char *);

};

#endif // !__CORE_H__
