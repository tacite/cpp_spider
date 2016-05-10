#ifndef		__IPROTOCOL_HPP__
# define		__IPROTOCOL_HPP__

#include	<exception>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<stdio.h>
#include	<cstring>
#include	<cstdint>
#include	<iostream>
#include	<string>
#include	<map>
#include	<vector>
#include	<stdexcept>

class						IProtocole {
public:
	virtual					~IProtocole(void) {}
	virtual void			_send(void) const = 0;
};
#endif // !__IPROTOCOL_HPP__
