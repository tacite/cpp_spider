#include "WSocket.h"
#include <stdlib.h>

WSocket::WSocket(void) {
	this->wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(this->wVersionRequested, &(this->wsaData)) != 0)
		throw std::exception("[Socket - Error] WSAStartup failed");
	if (LOBYTE(this->wsaData.wVersion) != 2 || HIBYTE(this->wsaData.wVersion) != 2)
		throw std::exception("[Socket - Error] Could not find a usable version of Winsock.dll");
	std::cout <<  "[Socket] Winsock 2.2 dll was found okay" << std::endl;
}

WSocket::~WSocket(void) {}

void WSocket::newSock(int iFamily, int iType, int iProtocol) {
	if ((this->sock_connect = WSASocketW(iFamily, iType, iProtocol, NULL, 0, 0)) == INVALID_SOCKET)
		throw std::exception("[Socket - Error] WSASocket function failed with error");
	else
		std::cout << "[Socket] WSASocket function succeeded" << std::endl;
}

void WSocket::_send(const char *data, int size) {
	if (size != send(this->sock_connect, data, size, 0))
	{
		throw std::exception("[Socket - Error] Send failed");
	}
}

char *WSocket::receive(unsigned int size) {
	char * buffer = new char[size];
	unsigned int i = 0;
	if ( (i = recv(this->sock_connect, buffer, size, 0)) == -1)
		throw std::exception("[Socket - Error] Recv operation failed");
	if (i == 0)
		throw std::exception("[Socket - Error] Disconnect");
 	return buffer;
}

void WSocket::connect(int iFamily, const std::string &ip, int port) {
	this->service.sin_family = iFamily;
	this->service.sin_addr.s_addr = inet_addr(ip.data());
	this->service.sin_port = htons(port);
	if (WSAConnect(this->sock_connect, (SOCKADDR *)&(this->service), sizeof(this->service), 0, 0, 0, 0) == SOCKET_ERROR)
		throw std::exception("[Socket - Error] Connect failed");
	std::cout << "[Socket] You're connected !" << std::endl;
}

int WSocket::getfd(void) const {
	return (int)this->sock_connect;
}