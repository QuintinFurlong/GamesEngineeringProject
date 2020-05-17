#pragma once
#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <SDL.h>
class WorkQueue
{
public:
	WorkQueue();
	void addTask(std::function<void()> newTask);
	void finish();
	std::function<void()> nextTask();
	bool hasWork();
private:
	SDL_cond* m_condition;
	SDL_mutex* m_lockQueue;
	bool finished;
	std::queue<std::function<void()>> m_tasks;
};