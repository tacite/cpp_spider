#include "HandleThreadSocket.h"
#include "Core.h"
#include "WThread.h"
#include "WSocket.h"
#include "WMutex.h"

HandleThreadSocket::HandleThreadSocket(Core * c)
{
	size = 0;
	result = false;
	t = new WThread();
	_m = new WMutex();
	_c = c;
	nb_thread_recv = 0;
	_m->initialize();
}

HandleThreadSocket::~HandleThreadSocket()
{
	t->destroyAll();
	delete(t);
}

unsigned int HandleThreadSocket::start(int o, void * arg)
{
	if (o == 1)
		return t->initialize(&HandleThreadSocket::send, arg);
	else if (o == 2)
		return t->initialize(&HandleThreadSocket::receive, arg);
	return t->initialize(&HandleThreadSocket::connect, arg);
}

void * HandleThreadSocket::send(void * arg)
{
	mData * Mythis = reinterpret_cast<mData *>(arg);
	try {
		Mythis->m->lock();
		Mythis->core->getSocket()->_send(Mythis->data, Mythis->size);
		Mythis->result = true;
		Mythis->m->unlock();
	}
	catch (const std::exception & msg)
	{
		Mythis->m->unlock();
		Mythis->core->setState(CLIENT_DISCONNECT);
		std::cerr << "[ERROR] Fail to send response : " << msg.what() << std::endl;
		Mythis->result = false;
	}
	return arg;
}

void * HandleThreadSocket::receive(void *arg)
{
	HandleThreadSocket * Mythis = reinterpret_cast<HandleThreadSocket *>(arg);
	try {
		char * header = NULL, *core = NULL;
		Mythis->_m->lock();
		if (!(header = Mythis->_c->getSocket()->receive(sizeof(packetHeader))))
			throw std::exception("");
		if (!(core = Mythis->_c->getSocket()->receive(Mythis->_c->getCommand().getTotalSize(header) - sizeof(packetHeader))))
			throw std::exception("");

		Mythis->_m->unlock();

		char * fullpacket = Mythis->_c->getCommand().fusionPacket(header, core);

		Mythis->_c->addResponse(fullpacket);
		Mythis->result = true;

	}
	catch (const std::exception & msg)
	{
		Mythis->_m->unlock();
		Mythis->_c->setState(CLIENT_DISCONNECT);
		std::cerr << "[ERROR] Fail to receive response : " << msg.what() << std::endl;
		Mythis->result = false;
		Mythis->data[(unsigned int)GetCurrentThreadId()] = NULL;
	}
	return arg;
}

void * HandleThreadSocket::connect(void * arg)
{
	HandleThreadSocket * Mythis = reinterpret_cast<HandleThreadSocket *>(arg);
	try {
		Mythis->_m->lock();
		Mythis->_c->getSocket()->connect(AF_INET, Mythis->ip, Mythis->port);
		Mythis->result = true;
		Mythis->_c->setState(CLIENT_CONNECTED);
		Mythis->_m->unlock();
	}
	catch (const std::exception & msg)
	{
		Mythis->_m->unlock();
		Mythis->_c->setState(CLIENT_DISCONNECT);
		std::cerr << "[ERROR] Fail to connect : " << msg.what() << std::endl;
		Mythis->result = false;
	}
	return arg;
}

bool HandleThreadSocket::connectSocket(std::string & _ip, unsigned int _port)
{
	ip = _ip;
	port = _port;
	result = false;
	unsigned int id = start(3, (void *)this);
	t->join();
	t->destroy(id);

	/*_c->getSocket()->connect(AF_INET, ip, port);
	result = true;
	_c->setState(CLIENT_CONNECTED);*/
	return result;
}

bool HandleThreadSocket::sendData(char * d, unsigned int s)
{
	mData * arg = new mData;
	arg->data = d;
	arg->size = s;
	
	arg->core = this->_c;
	arg->result = true;
	arg->m = _m;
	//std::cout << "Send " << s << std::endl;
	unsigned int id = start(1, (void *)(arg));
	this->_c->getSocket()->_send(d, s);

	t->join();
	t->destroy(id);
	//std::cout << "Send " << s << std::endl;
	return arg->result;
}

void HandleThreadSocket::receiveData()
{
	size = 0;
	result = false;
	nb_thread_recv++;
	//std::cout << "RECV" << std::endl;
	unsigned int id = start(2, (void *)this);

	t->join();
	/*char * header = NULL, *core = NULL;
	if (!(header = _c->getSocket()->receive(sizeof(packetHeader))))
		throw std::exception("");
	if (!(core = _c->getSocket()->receive(_c->getCommand().getTotalSize(header) - sizeof(packetHeader))))
		throw std::exception("");

	char * fullpacket = _c->getCommand().fusionPacket(header, core);

	_c->addResponse(fullpacket);*/
}

unsigned int HandleThreadSocket::getNbThreadRecv()
{
	return nb_thread_recv;
}

void HandleThreadSocket::decNbThreadRecv()
{
	nb_thread_recv--;
}