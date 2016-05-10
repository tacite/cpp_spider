#include	"Input.h"
#include <algorithm>

Input::Input()
{
	_isMouse = false;
	SecondTime = 0;
	NanoTime = 0;
	event = "UNKNOWN";
	pos_x = 0;
	pos_y = 0;
	amount = 0;
	ProcessName = "UNKNOWN";
	InputValue = "UNKNOWN";
}

Input::~Input()
{

}

void	Input::setSecondTime(int64_t s)
{
	SecondTime = s;
}

void	Input::setNanoTime(int64_t s)
{
	NanoTime = s;
}

void	Input::setProcessName(const std::string & p)
{
	ProcessName = p;
	std::replace(ProcessName.begin(), ProcessName.end(), ' ', '-');
}

void	Input::setInputValue(const std::string & p)
{
	InputValue = p;
}

void	Input::setPosX(uint32_t p)
{
	pos_x = p;
}
void	Input::setPosY(uint32_t p)
{
	pos_y = p;
}

void	Input::setAmount(uint64_t a)
{
	amount = a;
}

void	Input::setMouse(bool b)
{
	_isMouse = b;
}

void	Input::setEvent(const std::string & e)
{
	event = e;
}

std::string		Input::getEvent() const
{
	return event;
}

uint32_t	Input::getPosX() const
{
	return pos_x;
}

uint32_t	Input::getPosY() const
{
	return pos_y;
}

uint64_t	Input::getAmount() const
{
	return amount;
}

int64_t Input::getSecondTime() const
{
	return SecondTime;
}

int64_t Input::getNanoTime() const
{
	return NanoTime;
}

std::string Input::getProcessName() const
{
	return ProcessName;
}

std::string Input::getInputValue() const
{
	return InputValue;
}

bool	Input::isMouse() const
{
	return _isMouse;
}