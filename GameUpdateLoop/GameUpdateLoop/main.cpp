#include <iostream>
#include <Windows.h>
#include "GameTime.h"
#include <mutex>
using namespace std;

const float TRIGGER = 0.2f;

//static int counter = 0;
//mutex loc; static bool boo = true;
//void fun()
//{
//	
//	loc.lock();
//	counter++;
//	int temp = counter; //std::cout << "cunt : " << counter << std::endl;
//	loc.unlock();
//	
//	while (true)
//	{
//		loc.lock();
//		std::cout << "temp : " << temp << std::endl;
//		loc.unlock();
//	}
//}
//thread t1[100];
int main(void)
{
	//
	//for (int i = 0;i<100;i++)
	//{
	//	thread t2(fun);
	//	t1[i].swap(t2);
	//}
	//for (int i = 0; i < 100; i++)
	//{
	//	t1[i].join();
	//}
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";

	float last = 0.0f;
	float current = 0.0f;
	GameTime* gameTime = GameTime::getInstance();

	last = gameTime->running();

	//Main Game Loop
	while(true)
	{
		current = gameTime->running();
		if((current - last) > TRIGGER)
		{
			cout << "Update the Leprechauns!!!!";
			last = current;
		}
		Sleep(500);//main process sleeps
		cout << ".";//alive indicator
	}
}