#include "ThreadPool.h"
#include <mutex> 
static int num = 1;
std::mutex mtx;
void output()
{
	mtx.lock();
	std::cout << "happy birthday number :" << num << std::endl;
	num++;
	mtx.unlock();
}

int main2(int argc, char** argv)
{
	ThreadPool tp;
	for (int i = 0;i<10;i++)
	{
		tp.addTask(output);
	}
	tp.waitForCompletion();
	return 0;
}