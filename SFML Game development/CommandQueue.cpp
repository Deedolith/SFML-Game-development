#include "CommandQueue.h"

void CommandQueue::push(Command const& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command{ mQueue.front() };
	mQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
