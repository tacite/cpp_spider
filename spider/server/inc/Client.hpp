//
// Client.hpp for Client.hpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 19 22:34:23 2015 Florent BEAURAIN
// Last update Mon Oct 19 22:34:39 2015 Florent BEAURAIN
//

#ifndef         __CLIENT_HPP__
# define        __CLIENT_HPP__

# include		"ISocket.hpp"
# include		"Input.hpp"

class           Client {
public:
  Client(ISocket *);
  ~Client(void);

	ISocket		*getSocket(void) const;
	Input		*getInput(void) const;
	bool		_getMac(void) const;
	bool		_isIdentify(void) const;
	void		_setIdentify(bool);
	void		_receive(void);
	void		_send(void);

private:
	Input		*_input;
	ISocket		*_socket;
	bool		_identify;
	char		*_response;
};

#endif          /* !__CLIENT_HPP__ */
