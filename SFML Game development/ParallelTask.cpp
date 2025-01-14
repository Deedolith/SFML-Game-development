#include <SFML/System/Time.hpp>

#include "ParallelTask.h"

void ParallelTask::runTask()
{
	// Dummy task - stall 10 seconds
	bool ended = false;
	while (!ended)
	{
		mMutex.lock(); // Protect the clock 
		if (mElapsedTime.getElapsedTime().asSeconds() >= 10.f)
			ended = true;
		mMutex.unlock();
	}

	// mFinished may be accessed from multiple threads, protect it
	mMutex.lock();
	mFinished = true;
	mMutex.unlock();
}

ParallelTask::ParallelTask() :
	mElapsedTime{},
	mFinished{ false },
	mMutex{},
	mThread{}
{
}

ParallelTask::~ParallelTask()
{
	mThread.join();
}

void ParallelTask::execute()
{
	mFinished = false;
	mElapsedTime.restart();
	mThread = std::thread(&ParallelTask::runTask, this);
}

bool ParallelTask::isFinished()
{
	mMutex.lock();
	bool isFinished{ mFinished };
	mMutex.unlock();
	return isFinished;
}

float ParallelTask::getCompletion()
{
	mMutex.lock();
	float elapsedTime{ mElapsedTime.getElapsedTime().asSeconds() / 10.f };
	mMutex.unlock();
	return elapsedTime;
}
