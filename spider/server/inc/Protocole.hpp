#ifndef		__PROTOCOLE_HPP__
# define	__PROTOCOLE_HPP__

#include	"IProtocole.hpp"

#define MAX_INPUT_SEND 10

typedef struct
{
	uint8_t	lenght;
	uint8_t data[255];
}		string;

typedef struct
{
	uint8_t	size;
	string	data[255];
}		arrayString;

typedef struct
{
	int64_t		second;
	int64_t		nano;
	string		event;
	string		name;
	string		process;
}				keyboardPacket;

typedef struct
{
	int64_t		second;
	int64_t		nano;
	uint32_t	pos_x;
	uint32_t	pos_y;
	uint64_t	amount;
	string		event;
	string		name;
	string		process;
}				mousePacket;

typedef struct
{
	uint8_t	size;
	keyboardPacket data[MAX_INPUT_SEND];
}				arrayKeyboard;

typedef struct
{
	uint8_t	size;
	mousePacket data[255];
}				arrayMouse;

typedef struct
{
	uint8_t		opcode;
	uint8_t		id;
	uint16_t	size;
}				packetHeader;

typedef struct
{
	uint8_t		error;
	uint8_t		id;
}				errorResultPacket;

typedef struct
{
	uint8_t		mac[6];
}				macPacket;

typedef struct
{
	uint8_t		version;
}				versionPacket;

typedef	struct
{
	uint8_t		command;
}				commandPacket;

typedef struct
{
	arrayString	msg;
}				msgPacket;


class		Protocole : public IProtocole {
protected:
	versionPacket			version;
	macPacket				mac;
	packetHeader			header;
	arrayKeyboard			keyboard;
	arrayMouse				mouse;
public:
	Protocole(void);

	/* Getter Keyboard */
	uint8_t			_getSizeArrayKeyboard(void) const;
	int64_t			_getSecondKeyboard(size_t) const;
	int64_t			_getNanoKeyboard(size_t) const;
	uint8_t			_getLenghtProcessKeyboard(size_t) const;
	const uint8_t	*_getDataProcessKeyboard(size_t) const;
	uint8_t			_getLenghtNameKeyboard(size_t) const;
	const uint8_t	*_getDataNameKeyboard(size_t) const;
	uint8_t			_getLenghtEventKeyboard(size_t) const;
	const uint8_t	*_getDataEventKeyboard(size_t) const;

	/* Getter Mouse */
	uint8_t			_getSizeArrayMouse(void) const;
	int64_t			_getSecondMouse(size_t) const;
	int64_t			_getNanoMouse(size_t) const;
	uint8_t			_getLenghtProcessMouse(size_t) const;
	const uint8_t	*_getDataProcessMouse(size_t) const;
	uint8_t			_getLenghtNameMouse(size_t) const;
	const uint8_t	*_getDataNameMouse(size_t) const;
	uint8_t			_getLenghtEventMouse(size_t) const;
	const uint8_t	*_getDataEventMouse(size_t) const;

	/* Getter Mac */
	const uint8_t	*_getMac(void) const;

	/* Getter Version */
	uint8_t			_getVersion(void) const;

	/* Tools */
	std::string		_getDataFromString(string);
	char			*_getResponse(int);
	virtual ~Protocole(void);
	virtual void			_send(void) const;
};
#endif // !__PROTOCOLE_HPP__
