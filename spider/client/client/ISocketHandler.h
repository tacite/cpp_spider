#ifndef __ISOCKETHANDLER_H__
# define __ISOCKETHANDLER_H__

class ISocketHandler {
public:
	virtual ~ISocketHandler(void) {}
	virtual void newSock(int, int, int) = 0;
	virtual void connect(int, const std::string &, int) = 0;
	virtual void _send(const char *, int) = 0;
	virtual char *receive(unsigned int) = 0;
	virtual int getfd(void) const = 0;
};

#endif // !__ISOCKETHANDLER_H__
