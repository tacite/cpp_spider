#ifndef INPUT_H_
# define INPUT_H_

//#include	<Psapi.h>
#include	<Windows.h>
#include	<string>

class Input
{
private:	
	bool		_isMouse;
	int64_t		SecondTime;
	int64_t		NanoTime;
	std::string	event;
	uint32_t	pos_x;
	uint32_t	pos_y;
	uint64_t	amount;
	std::string	ProcessName;
	std::string	InputValue;
	

public:
	Input();
	~Input();

	void	setSecondTime(int64_t);
	void	setNanoTime(int64_t);
	void	setProcessName(const std::string &);
	void	setInputValue(const std::string &);
	void	setPosX(uint32_t);
	void	setPosY(uint32_t);
	void	setAmount(uint64_t);
	void	setMouse(bool);
	void	setEvent(const std::string &);

	int64_t getSecondTime() const;
	int64_t getNanoTime() const;
	std::string getProcessName() const;
	std::string getInputValue() const;
	uint32_t	getPosX() const;
	uint32_t	getPosY() const;
	uint64_t	getAmount() const;
	bool		isMouse() const;
	std::string 	getEvent() const;
};

#endif /* INPUT_H_ */