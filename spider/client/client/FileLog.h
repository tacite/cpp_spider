#ifndef  __FILELOG__
# define __FILELOG__

# include	"WMutex.h"
# include	"AHooker.hh"
# include	<string>
# include	<fstream>
# include	<iostream>
# include	<list>

class FileLog
{
private:
	std::string _fileName;
	static WMutex *_mutex;
public:
	FileLog();
	~FileLog();
	bool		initialize(const std::string &filename);
	bool		addInput(const Input & input);
	std::list<Input*> getInput();
};

#endif // !__FILELOG__
