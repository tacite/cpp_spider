#ifndef			__INPUT_HPP__
# define		__INPUT_HPP__

#include		<vector>
#include		"Protocole.hpp"
#include		"ISocket.hpp"
#include		"FileLog.hpp"

# define		OK				0
# define		IGNORED			1
# define		UNKNOWN_ERROR	2
# define		ALREADY_START	3
# define		ALREADY_END		4
# define		ALREADY_MUTE	5
# define		ALREADY_UNMUTE	6
# define		INVALID_CMD		7
# define		INVALID_KEY		8
# define		INVALID_MOUSE	9
# define		UNKNOWN_ID		10
# define		WRONG_VERSION	11
# define		WRONG_MAC		12
# define		CONNECT_FAIL	13
# define		DISCONNECT_FAIL	14

class			Input : public Protocole {
private:
	std::map<char, void(Input::*)(void)>	generateData;
	std::vector<char *>						_msg;
	char									*msg;
	bool									isMac;
	int										status;
	int										_isConnected;
	FileLog									*_fileLog;

	/* Commandes */
	void	_mac(void);
	void	_version(void);
	void	_connect(void);
	void	_disconnect(void);
	void	_log(void);
	void	_cmdsrv(void);
	void	_ping(void);
	void	_pong(void);
	void	_keyboard(void);
	void	_mouse(void);

public:
	Input(void);
	~Input(void);

	void					_receive(ISocket *);
	std::vector<char *>		&_getListMsg(void);
	bool					_getIsMac(void) const;
	int						_getStatus(void) const;
	void					_writeLog(void);
};

#endif // !__INPUT_HPP__
