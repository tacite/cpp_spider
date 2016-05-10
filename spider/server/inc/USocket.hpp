//
// USocket.hpp for USocket.hpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 15:36:20 2015 Florent BEAURAIN
// Last update Mon Oct 26 15:36:22 2015 Florent BEAURAIN
//

#ifndef						__USOCKET_HPP__
# define					__USOCKET_HPP__

# include					<sys/socket.h>
# include					<sys/types.h>
# include					<netinet/in.h>
# include					<arpa/inet.h>
# include					<netdb.h>
# include					<unistd.h>
# include					<cstdlib>
# include					<cerrno>
# include					<cstring>
# include					<exception>
# include					<iostream>
# include					<stdexcept>
# include					"ISocket.hpp"

class						USocket : public ISocket {
public:
	USocket(int fd = -1);
	virtual ~USocket(void);

	virtual void				_socket(int socket_family, int socket_type, int protocol);
	virtual void				_bind(int socket_family, int port);
	virtual void				_listen(int backlog) const;
	virtual USocket				*_accept(void);
	virtual void				_select(int sec, int usec);
	virtual void				_FD_ZERO(std::string mode);
	virtual void				_FD_SET(std::string mode);
	virtual void				_FD_SET(const ISocket *, std::string mode);
	virtual bool				_FD_ISSET(char mode) const;
	virtual bool				_FD_ISSET(const ISocket *, char mode) const;
	virtual void				_close(void);
	virtual char *				_read(size_t size);
	virtual void				_write(char *, size_t) const;
	virtual std::string		_readCmd(void);

	virtual int					getfd(void) const;

	virtual USocket				&operator<<(const std::string &);
	virtual USocket				&operator>>(std::string &);

private:
	int						_fd;
	int						_fd_max;
	fd_set					_readfds;
	fd_set					_writefds;
};

#endif					/* !__USOCKET_HPP__ */
