/* 
   
 */

#ifndef _HookerMouse_hh_
#define _HookerMouse_hh_

#include	"AHooker.hh"

class HookerMouse : AHooker
{
public:
	HookerMouse();
	~HookerMouse();
	std::string	GetInput();
	Input		OrderInput(int ToOrder);
	std::string	GetSyntax(int a);
	std::string	GetWindowTitle();
	std::string	GetKeyboardSyntax();
	//LRESULT CALLBACK MyProc(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif /* _HookerMouse_hh_ */

