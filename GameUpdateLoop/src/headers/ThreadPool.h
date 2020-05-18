#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "WorkQueue.h"

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();
	void addTask(std::function<void()>);
	void waitForCompletion();
	WorkQueue workQueue;
private:
	std::vector<SDL_Thread *> m_threads;
	std::queue<std::function<void()>> m_tasks;
	
};
#endif // !THREAD_POOL_H

