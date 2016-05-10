#include "USocket.h"

USocket::USocket(void) {
	this->fd_serv = 0;
	this->h = NULL;
}

USocket::~USocket(void) {}

void				USocket::newSock(int iFamily, int iType, int iProtocol) {
	if ((this->fd_serv = socket(iFamily, iType, 0)) == -1)
		throw std::exception("[Socket - error] newSock : socket function failed");
}

void				USocket::connect(int iFamily, const std::string &ip, int port) {
	if ((this->h = gethostbyname(ip)) == NULL)
		throw std::exception("[Socket - error] connect : gethostbyname function failed");
	bcopy(h->h_addr, &(this->addr), sizeof(this->addr));
	this->s_in.sin_family = iFamily;
	this->s_in.sin_port = htons(port);
	this->s_in.sin_addr.s_addr = inet_addr(inet_ntoa(this->addr));
	if (connect(this->fd_serv, (struct sockaddr *)&(this->s_in), sizeof(struct sockaddr_in)) == -1)
		throw std::exception("[Socket - error] connect : connect function failed");
}

void				USocket::send(const std::string &msg) {
	if (!write(this->fd_serv, msg.data(), len(msg)))
		throw std::exception("[Socket - error] send : write function failed");
}

virtual char		USocket::*receive(void) {

}