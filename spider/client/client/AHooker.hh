#ifndef _AHooker_hh_
#define _AHooker_hh_

#include	<iostream>
#include	<Windows.h>
#include	<Psapi.h>
#include	"Input.h"


class			AHooker
{
  public:
	  ~AHooker() {};
    virtual std::string GetInput() = 0;
    virtual Input OrderInput(int ToOrder) = 0;
	virtual	std::string	GetSyntax(int a) = 0;
	virtual	std::string	GetWindowTitle() = 0;
	virtual	std::string	GetKeyboardSyntax() = 0;
	//virtual	LRESULT CALLBACK	MyProc(int nCode, WPARAM wParam, LPARAM lParam) = 0;
};

#endif /* _AHooker_hh_ */

