#ifndef					__USOCKET_HPP__
# define				__USOCKET_HPP__

# include				<sys/socket.h>
# include				<netinet/in.h>
# include				<arpa/inet.h>
# include				<netdb.h>
# include				"ISocketHandler.h"

class					USocket : public ISocketHandler {
private:
	int					fd_serv;
	struct sockaddr_in	s_in;
	struct in_addr		addr;
	struct hostent		*h;
public:
	USocket(void);
	virtual ~USocket(void);

	virtual void		newSock(int, int, int);
	virtual void		connect(int, const std::string &, int);
	virtual void		send(const std::string &);
	virtual char		*receive(void);
};

#endif // !__USOCKET_HPP__
