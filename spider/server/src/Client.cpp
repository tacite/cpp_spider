//
// Client.cpp for Client.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider/server/src
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Tue Oct 20 12:09:05 2015 Florent BEAURAIN
// Last update Tue Oct 20 12:09:06 2015 Florent BEAURAIN
//

#include			"Client.hpp"

/*
** Constructeurs & Destructeurs
*/

Client::Client(ISocket *socket) {
	_socket = socket;
	_identify = false;
	_input = new Input();
}

Client::~Client(void) {
	delete _socket;
}

/*
** Getters
*/

ISocket			*Client::getSocket(void) const {
	return _socket;
}

bool			Client::_isIdentify(void) const {
	return _identify;
}

Input			*Client::getInput(void) const {
	return _input;
}

bool			Client::_getMac(void) const {
	return _input->_getIsMac();
}

/*
** Méthodes
*/

void			Client::_receive(void)
{
	this->_input->_receive(this->_socket);
}

void			Client::_send(void) {
	while (_input->_getListMsg().size() > 0) {
		_socket->_write(_input->_getListMsg()[0], sizeof(packetHeader) + sizeof(errorResultPacket));
		_input->_getListMsg().erase(_input->_getListMsg().begin());
	}
}

void			Client::_setIdentify(bool b) {
	_identify = b;
}