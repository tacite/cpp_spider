#include	<ctime>
#include	"HookerMouse.hh"

HookerMouse::HookerMouse()
{

}

HookerMouse::~HookerMouse()
{

}

std::string		HookerMouse::GetInput()
{
	return "";
}

Input			HookerMouse::OrderInput(int a)
{
	Input		ret;
	std::time_t result = std::time(nullptr);
	SYSTEMTIME	DaTime;

	GetSystemTime(&DaTime);
	ret.setMouse(false);
	ret.setProcessName(this->GetWindowTitle());
	ret.setInputValue(this->GetSyntax(a));
	ret.setSecondTime(result);
	ret.setNanoTime(DaTime.wMilliseconds * 1000);
	ret.setMouse(true);
	return ret;
}

std::string		HookerMouse::GetKeyboardSyntax()
{
	char		KeyName[KL_NAMELENGTH];

	GetKeyboardLayoutName(KeyName);
	if (strcmp(KeyName, "0000040C") == 0)
		return ("French(Standard)");
	if (strcmp(KeyName, "00000409") == 0)
		return ("English(United States)");
	if (strcmp(KeyName, "00000809") == 0)
		return ("English(United Kingdom)");
	if (strcmp(KeyName, "00000419") == 0)
		return ("Russian");
	return (KeyName);
}

std::string		HookerMouse::GetWindowTitle()
{
	DWORD		ret = 0;

	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	GetWindowThreadProcessId(hwnd, &ret);

	int len = GetWindowTextLength(hwnd);
	TCHAR *winBuf = new TCHAR[len];
	GetWindowText(hwnd, winBuf, len + 1);

	if (ret != 0)
	{
		HANDLE hProcess = OpenProcess((PROCESS_QUERY_INFORMATION | PROCESS_VM_READ), FALSE, ret);
		LPSTR lpszFilename = new CHAR[MAX_PATH];
		GetModuleFileNameEx(hProcess, NULL, lpszFilename, MAX_PATH);
		CloseHandle(hProcess);
		return (lpszFilename);
	}
	else
		return ("Could  not get process id for foreground window.");
	return "";
}

std::string		HookerMouse::GetSyntax(int a)
{
	std::string	ret;

	if (a == 0)
		return ("left");
	if (a == 1)
		return ("right");
	return ("move");
}