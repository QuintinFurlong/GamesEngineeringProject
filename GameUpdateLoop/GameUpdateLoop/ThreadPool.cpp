#include "ThreadPool.h"

int getWork(void* thing)
{
	std::function<void()> moreWork;
	WorkQueue* workQueue = (WorkQueue*)thing;
	while (moreWork = workQueue->nextTask())
	{
		moreWork();
	}
	return 0;
}

ThreadPool::ThreadPool() {
	int cores = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < cores; i++)
	{
		m_threads.push_back(SDL_CreateThread(getWork, "workQTime", &workQueue));
		// Need to add a function thats listens for 
		// Tasks to be added to the queue
	}
}

ThreadPool::~ThreadPool() 
{
	workQueue.finish();
	waitForCompletion();
	for (int i = 0; i < m_threads.size(); i++)
	{
		SDL_WaitThread(m_threads[i],NULL);
	}
}


void ThreadPool::addTask(std::function<void()> task) 
{
	//m_tasks.push(task);
	workQueue.addTask(task);
}

void ThreadPool::waitForCompletion()
{
	while (workQueue.hasWork())
	{

	}
}

