//
// Server.hpp for Server.hpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 19 22:02:53 2015 Florent BEAURAIN
// Last update Mon Oct 19 22:02:55 2015 Florent BEAURAIN
//

#ifndef                 __SERVER_HPP__
# define                __SERVER_HPP__

# include               <exception>
# include               <iostream>
# include               <vector>
# include					<algorithm>
# include               "Client.hpp"
# include					"USocket.hpp"
# include					"Input.hpp"
# include				"FileLog.hpp"

# define		RED			"\x1B[31m"
# define		GREEN		"\033[32m"
# define		YELLOW		"\033[33m"
# define		BLUE		"\033[34m"
# define		PURPLE		"\033[35m"
# define		WHITE		"\x1B[0m"
# define		CYAN		"\x1B[36m"
# define		HIGHLIGHT	"\033[1m"
# define		DEFAULT		"\033[0m"
# define		BLINK		"\033[5m"
# define		UNDERLINE	"\033[4m"


class                   Server {
public:
  Server(void);
  ~Server(void);

  void                  run(void);
  void                  init(char *);

private:
	FileLog					*_filelog;
	ISocket					*_socket;
	std::vector<Client *> _listClient;

	void						newClient(void);
	void						deleteClient(unsigned int);
	void						setClient(void);
	bool						readClient(unsigned int);
	void						writeClient(unsigned int);
};

#endif                 /* !__SERVER_HPP__ */
