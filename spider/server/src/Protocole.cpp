#include "Protocole.hpp"

Protocole::Protocole(void) {
}

Protocole::~Protocole(void) {}

std::string			Protocole::_getDataFromString(string t) {
	char st[255];
	std::cout << (int)t.lenght << std::endl;
	for (unsigned int i = 0; i < t.lenght; i++)
		st[i] = (char)t.data[i];
	st[t.lenght] = 0;
	return std::string(st);
}

void				Protocole::_send(void) const {

}


/* Getter Keyboard */

uint8_t			Protocole::_getSizeArrayKeyboard(void) const {
	return this->keyboard.size;
}

int64_t			Protocole::_getSecondKeyboard(size_t pos) const {
	return this->keyboard.data[pos].second;
}

int64_t			Protocole::_getNanoKeyboard(size_t pos) const {
	return this->keyboard.data[pos].nano;
}

uint8_t			Protocole::_getLenghtProcessKeyboard(size_t pos) const {
	return this->keyboard.data[pos].process.lenght;
}

const uint8_t	*Protocole::_getDataProcessKeyboard(size_t pos) const {
	return this->keyboard.data[pos].process.data;
}

uint8_t			Protocole::_getLenghtNameKeyboard(size_t pos) const {
	return this->keyboard.data[pos].name.lenght;
}

const uint8_t	*Protocole::_getDataNameKeyboard(size_t pos) const {
	return this->keyboard.data[pos].name.data;
}

uint8_t			Protocole::_getLenghtEventKeyboard(size_t pos) const {
	return this->keyboard.data[pos].event.lenght;
}

const uint8_t	*Protocole::_getDataEventKeyboard(size_t pos) const {
	return this->keyboard.data[pos].event.data;
}


/* Getter Mouse */

uint8_t			Protocole::_getSizeArrayMouse(void) const {
	return this->mouse.size;
}

int64_t			Protocole::_getSecondMouse(size_t pos) const {
	return this->mouse.data[pos].second;
}

int64_t			Protocole::_getNanoMouse(size_t pos) const {
	return this->mouse.data[pos].nano;
}

uint8_t			Protocole::_getLenghtProcessMouse(size_t pos) const {
	return this->mouse.data[pos].process.lenght;
}

const uint8_t	*Protocole::_getDataProcessMouse(size_t pos) const {
	return this->mouse.data[pos].process.data;
}

uint8_t			Protocole::_getLenghtNameMouse(size_t pos) const {
	return this->mouse.data[pos].name.lenght;
}

const uint8_t	*Protocole::_getDataNameMouse(size_t pos) const {
	return this->mouse.data[pos].name.data;
}

uint8_t			Protocole::_getLenghtEventMouse(size_t pos) const {
	return this->mouse.data[pos].event.lenght;
}

const uint8_t	*Protocole::_getDataEventMouse(size_t pos) const {
	return this->mouse.data[pos].event.data;
}

/* Getter Mac */

const uint8_t	*Protocole::_getMac(void) const {
	if (this->mac.mac[0])
		return this->mac.mac;
	return NULL;
}

/* Getter Version */

uint8_t			Protocole::_getVersion(void) const {
	return this->version.version;
}

char			*Protocole::_getResponse(int error) {
	packetHeader h;
	errorResultPacket p;
	char *result = new char[sizeof(packetHeader) + sizeof(errorResultPacket)];
	memset(&h, 0, sizeof(packetHeader));
	memset(&p, 0, sizeof(errorResultPacket));
	memset(result, 0, sizeof(packetHeader) + sizeof(errorResultPacket));
	h.opcode = 0;
	h.id = 42;
	h.size = sizeof(errorResultPacket);
	p.error = error;
	p.id = this->header.id;
	memcpy(result, &h, sizeof(packetHeader));
	memcpy(result + sizeof(packetHeader), &p, sizeof(errorResultPacket));
	return result;
}