//
// USocket.cpp for USocket.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 15:44:59 2015 Florent BEAURAIN
// Last update Mon Nov  2 13:04:11 2015 Florent BEAURAIN
//

#include		"USocket.hpp"

/*
** Constructeurs & Destructeurs
*/

USocket::USocket(int fd) {
	_fd = fd;
	_fd_max = fd;
	_FD_ZERO("rw");
}

USocket::~USocket(void) {
	_close();
}

/*
** Getters
*/

int					USocket::getfd(void) const {
	return _fd;
}

/*
** Méthodes
*/

void					USocket::_socket(int socket_family, int socket_type, int protocol) {
	struct protoent		*pe;
	(void)protocol;

	if (socket_type == SOCK_STREAM) {
		if ((pe = getprotobyname("TCP")) == NULL)
			throw std::runtime_error(strerror(errno));
	}
	else if (socket_type == SOCK_DGRAM) {
		if ((pe = getprotobyname("UDP")) == NULL)
			throw std::runtime_error(strerror(errno));
	}
	else
		throw std::runtime_error("[Error] : bad protocol");

	if ((_fd = socket(socket_family, socket_type, pe->p_proto)) == -1) {
		throw std::runtime_error(strerror(errno));
		}

	_fd_max = _fd;
	_FD_ZERO("rw");

	return;
}

void					USocket::_bind(int socket_family, int port) {
	struct sockaddr_in	s_in;

	s_in.sin_family = socket_family;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = htons(INADDR_ANY);
	if (bind(_fd, reinterpret_cast<const struct sockaddr *>(&s_in), sizeof(s_in)) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

void					USocket::_listen(int backlog) const {
	if (listen(_fd, backlog) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

USocket				*USocket::_accept(void) {
	int						fd;
	struct sockaddr_in	s_in;
	socklen_t            sin_len = sizeof(s_in);

	if ((fd = accept(_fd, reinterpret_cast<struct sockaddr *>(&s_in), &sin_len)) == -1)
		throw std::runtime_error(strerror(errno));
	if (_fd_max < fd)
		_fd_max = fd;

	USocket	*newConnection = new USocket(fd);
	return newConnection;
}

void					USocket::_select(int sec, int usec) {
	struct timeval	tv;

  	tv.tv_sec = sec;
  	tv.tv_usec = usec;
	if (select(_fd_max + 1, &_readfds, &_writefds, NULL, &tv) == -1) {
		throw std::runtime_error(strerror(errno));
	}

	return;
}

void					USocket::_FD_ZERO(std::string mode) {
	if (mode == "r")
		FD_ZERO(&_readfds);
	else if (mode == "w")
		FD_ZERO(&_writefds);
	else if (mode == "rw") {
		FD_ZERO(&_readfds);
		FD_ZERO(&_writefds);
	}
	else
		std::runtime_error("[Error]: bad mode for _FD_ZERO()");

	return;
}

void					USocket::_FD_SET(std::string mode) {
	if (mode == "r")
		FD_SET(_fd, &_readfds);
	else if (mode == "w")
		FD_SET(_fd, &_writefds);
	else if (mode == "rw") {
		FD_SET(_fd, &_readfds);
		FD_SET(_fd, &_writefds);
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_SET()");

	return;
}

void					USocket::_FD_SET(const ISocket *socket, std::string mode) {
	if (mode == "r")
		FD_SET(socket->getfd(), &_readfds);
	else if (mode == "w")
		FD_SET(socket->getfd(), &_writefds);
	else if (mode == "rw") {
		FD_SET(socket->getfd(), &_readfds);
		FD_SET(socket->getfd(), &_writefds);
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_SET()");

	return;
}

bool					USocket::_FD_ISSET(char mode) const {
	if (mode == 'r') {
			if (FD_ISSET(_fd, &_readfds))
				return true;
		}
		else if (mode == 'w') {
			if (FD_ISSET(_fd, &_writefds))
				return true;
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_ISSET()");

	return false;
}

bool					USocket::_FD_ISSET(const ISocket *socket, char mode) const {
	if (mode == 'r') {
		if (FD_ISSET(socket->getfd(), &_readfds))
			return true;
	}
	else if (mode == 'w') {
		if (FD_ISSET(socket->getfd(), &_writefds))
			return true;
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_ISSET()");

	return false;
}

void					USocket::_close(void) {
	if (close(_fd) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

std::string			USocket::_recv(int flags) {
	char				buffer[30721];
	std::string		msg;
	ssize_t			ret;

	if ((ret = recv(_fd, buffer, 30720, flags)) <= 0)
		throw std::runetime_error(strerror(errno));
	buffer[ret] = '\0';
	msg.append(buffer);

	return msg;
}

std::string			USocket::_recv(ssize_t size, int flags) {
	char				buffer[size + 1];
	std::string		msg;
	ssize_t			ret;

	if ((ret = recv(_fd, buffer, size, flags)) <= 0)
		throw std::runetime_error(strerror(errno));
	buffer[ret] = '\0';
	msg.append(buffer);

	return msg;
}

void					USocket::_send(const std::string msg, int flags) {
	ssize_t			ret;

	if ((ret = send(_fd, msg.c_str(), msg.size(), flags)) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

void					USocket::_send(const std::string msg, ssize_t size, int flags) {
	ssize_t			ret;

	if ((ret = send(_fd, msg.c_str(), size, flags)) == -1)
		throw std::runetime_error(strerror(errno));

	return;
}

std::string			USocket::_read(void) {
	char				buffer[30721];
	std::string		msg;
	ssize_t			ret;

	if ((ret = read(_fd, buffer, 30720)) <= 0)
		throw std::runetime_error(strerror(errno));
	buffer[ret] = '\0';
	msg.append(buffer);

	return msg;
}

std::string			USocket::_read(size_t size) {
	char				buffer[size + 1];
	std::string		msg;
	ssize_t			ret;

	if ((ret = read(_fd, buffer, size)) <= 0)
		throw std::runetime_error(strerror(errno));
	buffer[ret] = '\0';
	msg.append(buffer);

	return msg;
}

void					USocket::_write(const std::string msg) {
	ssize_t			ret;

	if ((ret = write(_fd, msg.c_str(), msg.size()) == -1)
		throw std::runetime_error(strerror(errno));

	return;
}

void					USocket::_write(const std::string msg, size_t size) {
	ssize_t			ret;

	if ((ret = write(_fd, msg.c_str(), size)) == -1)
		throw std::runetime_error(strerror(errno));

	return;
}
