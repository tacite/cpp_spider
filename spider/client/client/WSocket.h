#ifndef __WSOCKET_H__
# define __WSOCKET_H__
# define _WINSOCK_DEPRECATED_NO_WARNINGS
# define SEND_COUNT 10

#include <string>
#include <iostream>
//#include <WS2tcpip.h>
#include <winsock2.h>
#include <windows.h>


#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")


#include "ISocketHandler.h"

class WSocket : public ISocketHandler {
private:
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET sock_connect;
	sockaddr_in service;
	sockaddr_in saClient;
	WSABUF DataBuf;
	WSAOVERLAPPED SendOverlapped;
	WSAOVERLAPPED RecvOverlapped;
public:
	WSocket(void);
	virtual ~WSocket(void);
	virtual void newSock(int, int, int);
	virtual void connect(int, const std::string &, int);
	virtual void _send(const char *, int);
	virtual char *receive(unsigned int);
	virtual int getfd(void) const;
};

#endif // !__WSOCKET_H__
