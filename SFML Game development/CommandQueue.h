#pragma once

#include <queue>

#include "Command.h"

class CommandQueue
{
private:
	std::queue<Command> mQueue;
public:
	void push(Command const& command);
	Command pop();
	bool isEmpty() const;
};

