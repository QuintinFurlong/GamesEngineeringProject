#include "GameTime.h"

GameTime::GameTick()
{
	elapsed = 0.0f; //initalise at 0
	running = 0.0f; //initialise at 0
};

void GameTick::update()
{
	elapsed = increment;
	running += increment;
};

