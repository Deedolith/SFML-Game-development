#pragma once

#include <thread>
#include <mutex>

#include <SFML/System/Clock.hpp>

class ParallelTask
{
private:
	std::thread mThread;
	bool mFinished;
	sf::Clock mElapsedTime;
	std::mutex mMutex;
private:
	void runTask();
public:
	ParallelTask();
	~ParallelTask();
	void execute();
	bool isFinished();
	float getCompletion();
};
