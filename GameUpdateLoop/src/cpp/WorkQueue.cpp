#include "WorkQueue.h"


WorkQueue::WorkQueue()
	: m_condition(SDL_CreateCond())
	, m_lockQueue(SDL_CreateMutex())
{
}


// ADDING TASKS TO THE QUEUE
///////////////////////////////////////////////////////
void WorkQueue::addTask(std::function<void()> newTask)
{
	if (!finished)
	{
		SDL_LockMutex(m_lockQueue);		// Lock Task Queue
		m_tasks.push(newTask);			// Push new task
		SDL_CondSignal(m_condition);	// Restarts Threads waiting on m_condition
		SDL_UnlockMutex(m_lockQueue);	// Lock Task Queue
	}
}
// ADDING TASKS TO THE QUEUE
///////////////////////////////////////////////////////
std::function<void()> WorkQueue::nextTask()
{
	std::function<void()> nextJob = 0;
	SDL_LockMutex(m_lockQueue);							// Lock Task Queue
	if (finished && m_tasks.size() == 0)
	{
		nextJob = 0;
	}
	else
	{
		while (m_tasks.size() == 0)
		{
			SDL_CondWait(m_condition, m_lockQueue);		// Wait while theres no jobs
		}
		nextJob = m_tasks.front();
		m_tasks.pop();									// Pop job of the front of the queue
	}
	SDL_UnlockMutex(m_lockQueue);						// Unlock Task Queue
	return nextJob;
}
// FINISH
///////////////////////////////////////////////////////
void WorkQueue::finish()
{
	SDL_LockMutex(m_lockQueue);			// Lock Task Queue 
	finished = true;
	SDL_CondSignal(m_condition);		// Lock Task Queue 
	SDL_UnlockMutex(m_lockQueue);		// Lock Task Queue 

	SDL_DestroyMutex(m_lockQueue);		// Cleanup mutex
	SDL_DestroyCond(m_condition);		// Cleanup condition
}

bool WorkQueue::hasWork()
{
	return m_tasks.size() > 0;
}

