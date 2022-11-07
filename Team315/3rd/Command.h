#pragma once
#include <deque>

enum class CmdTypes
{
	None = -1,
	Move,
	Action,
	Count
};

// number, target 수정해야 함
class Command
{
protected:
	CmdTypes cmdType;
	std::deque<int>* target;
	int number;

public:
	Command(CmdTypes type)
		: cmdType(type), target(nullptr), number(0) {}
	virtual ~Command() {};

	virtual void Set(std::deque<int>* target, int number = 0)
	{
		this->target = target;
		this->number = number;
	}

	virtual bool Do() = 0;
	virtual bool UnDo() = 0;
	virtual bool ReDo() { return Do(); }

	virtual void Init() = 0;
	virtual void Reset()
	{
		target = nullptr;
		number = 0;
	};

	CmdTypes GetType() const { return cmdType; }
	int GetNumber() const { return number; }
};