#include "FileLog.h"
#include <iostream>
#include <sstream>

FileLog::FileLog()
{
}

FileLog::~FileLog()
{
}

WMutex* FileLog::_mutex = NULL;

bool	FileLog::initialize(const std::string &filename)
{
	if (_mutex == NULL)
	{
		_mutex = new WMutex();
		if (!_mutex->initialize())
			return false;
	}
	this->_fileName = filename;
	return (true);
}

bool	FileLog::addInput(const Input & input)
{
	_mutex->lock();
	std::ofstream file(this->_fileName, std::ios::out | std::ios::app);

	if (file)
	{
		if (input.isMouse())
			file << 1 << " ";
		else
			file << 0 << " ";
		file << input.getSecondTime() << " " << input.getNanoTime() << " ";
		file << input.getProcessName() << " " << input.getInputValue() << " ";
		if (input.isMouse())
			file << input.getPosX() << " " << input.getPosY() << " " << input.getAmount() << " ";
		file << input.getEvent() << std::endl;
		file.close();
		_mutex->unlock();
		return true;
	}
	_mutex->unlock();
	return (false);
}

std::list<Input *>	FileLog::getInput()
{
	_mutex->lock();
	std::ifstream file(this->_fileName, std::ios::in);
	std::list<Input *>	myList;
	Input					*input;
	Input					*save;
	if (file)
	{
		std::string	l;
		int64_t tmp = 0;
		std::string t;
		save = new Input;
		while (getline(file, l))
		{
			//std::cout << l << std::endl;
			std::istringstream line(l);
			input = new Input;
			line >> tmp;
			if (tmp == 1) // mouse
				input->setMouse(true);
			tmp = 0;
			line >> tmp;
			//std::cout << "Second time : " << (int)(tmp) << std::endl;
			input->setSecondTime(tmp);
			tmp = 0;
			line >> tmp;
			//std::cout << "Nano time : " << (int)(tmp) << std::endl;
			input->setNanoTime(tmp);
			tmp = 0;
			t = "";
			line >> t;
			//std::cout << "Process Name : " << (t) << std::endl;
			input->setProcessName(t);
			t = "";
			line >> t;
			//std::cout << "Input : " << (t) << std::endl;
			input->setInputValue(t);

			if (input->isMouse())
			{
				uint32_t pos = 0;
				line >> pos;
				//std::cout << " pos X : " << (int)(pos) << std::endl;
				input->setPosX(pos);
				pos = 0;
				line >> pos;
				//std::cout << " pos Y : " << (int)(pos) << std::endl;
				input->setPosY(pos);
				pos = 0;
				uint64_t amount = 0;
				line >> amount;
				//std::cout << " amount : " << (int)(amount) << std::endl;
				input->setAmount(amount);
			}
			t = "";
			line >> t;
			//std::cout << "Event : " << (t) << std::endl;
			input->setEvent(t);
			if (save->getNanoTime() == 0 && input->isMouse() == false)
			{
				save = input;
			}
			else if (input->isMouse() == false)
			{
				save->setInputValue(save->getInputValue() + input->getInputValue());
			}
			if (input->isMouse())
			{
				if (save->getNanoTime() != 0)
				{
					myList.push_back(save);
				}
				myList.push_back(input);
				save = new Input;
			}
			else if (input->getInputValue().compare("<tab>") == 0 || input->getInputValue().compare("<enter>") == 0)
			{
				myList.push_back(save);
//				delete input;
				save = new Input;
			}
		}
		file.close();
	}
	else
	{
		_mutex->unlock();
		return myList;
	}
	std::ofstream file2(this->_fileName, std::ios::out | std::ios::trunc);
	
	if (file2)
		file2.close();
	_mutex->unlock();
	return (myList);
}