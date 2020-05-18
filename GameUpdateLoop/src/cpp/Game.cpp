#include <Game.h>
#include <iostream>
#include <thread>


using namespace std;

Game::Game() : m_running(false)
{
}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_p_Window != 0)
		{
			DEBUG_MSG("Window creation success");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
			}
			else
			{
				DEBUG_MSG("Renderer init fail");
				return false;
			}
		}
		else
		{
			DEBUG_MSG("Window init fail");
			return false;
		}
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}
	m_running = true;

	return true;
}



void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");
	m_p_Surface = SDL_LoadBMP("assets/sprite.bmp");
	m_p_Texture = SDL_CreateTextureFromSurface(m_p_Renderer, m_p_Surface);
	SDL_FreeSurface(m_p_Surface);

	if(SDL_QueryTexture(m_p_Texture, NULL, NULL, &m_Source.w, &m_Destination.h)==0)
	{
		m_Destination.x = m_Source.x = 0;
		m_Destination.y = m_Source.y = 0;
		m_Destination.w = m_Source.w;
		m_Destination.h = m_Source.h;

		DEBUG_MSG("Destination X:" + m_Destination.x);
		DEBUG_MSG("Destination Y:" + m_Destination.y);
		DEBUG_MSG("Destination W:" + m_Destination.w);
		DEBUG_MSG("Destination H:" + m_Destination.h);
	}
	else
	{
		DEBUG_MSG("Texture Query Failed");
		m_running = false;
	}
	m_activeCount = 30;
	m_nextCount = 30;
	m_activeNPCCount = 5; 
	int blockSize = 1000 / m_activeCount;
	int grid = 0;
	if (blockSize != 1)
	{
		grid = 1;
	}
	for (int i=0;i< m_activeCount;i++)
	{
		for (int i2 = 0; i2 < m_activeCount; i2++)
		{
			m_block[i][i2] = { i* blockSize, i2* blockSize,blockSize- grid,blockSize- grid };
		}
	}
	grid++;
	int tenthOfSize = abs(m_activeCount * 0.1f);
	for (int i = 0; i < m_activeNPCCount; i++) 
	{
		m_npc[i] = { ((tenthOfSize * 6) + (rand()%(tenthOfSize * 3))) * blockSize, ((tenthOfSize * 2) + rand() % (tenthOfSize * 4)) * blockSize ,
		blockSize /grid, blockSize  / grid};
	}

}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_p_Renderer);
	DEBUG_MSG("Width Source" + m_Destination.w);
	DEBUG_MSG("Width Destination" + m_Destination.w);

	for (int i = 0; i < m_activeCount; i++)
	{
		for (int i2 = 0; i2 < m_activeCount; i2++)
		{
			if ((i+i2)%2!=2)
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
			//SDL_SetRenderDrawColor(m_p_Renderer, ((200+i)%255), ((200 + i2)%255), ((i+i2) % 255), 255);
			SDL_RenderFillRect(m_p_Renderer, &m_block[i][i2]);
		}
	}
	SDL_SetRenderDrawColor(m_p_Renderer, 255, 0, 0, 255);
	for (int i = 0; i < m_activeNPCCount; i++)
	{
		SDL_RenderFillRect(m_p_Renderer, &m_npc[i]);
	}
	m_p_Window;

	if (m_p_Renderer != nullptr && m_p_Texture != nullptr)
	{
		//SDL_RenderCopy(m_p_Renderer, m_p_Texture, NULL, NULL);
	}
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	if (m_activeCount != m_nextCount)
	{
		m_activeCount = m_nextCount;
		int blockSize = 1000 / m_activeCount;
		int grid = 0;
		if (blockSize != 1)
		{
			grid = 1;
		}
		for (int i = 0; i < m_activeCount; i++)
		{
			for (int i2 = 0; i2 < m_activeCount; i2++)
			{
				m_block[i][i2] = { i * blockSize, i2 * blockSize,blockSize - grid,blockSize - grid };
			}
		}
		grid++;
		int tenthOfSize = abs(m_activeCount * 0.1f);
		for (int i = 0; i < m_activeNPCCount; i++)
		{
			m_npc[i] = { ((tenthOfSize * 6) + (rand() % (tenthOfSize * 3))) * blockSize, ((tenthOfSize * 2) + rand() % (tenthOfSize * 4)) * blockSize ,
			blockSize / grid, blockSize / grid };
		}
	}
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (m_activeCount== m_nextCount)
		{
			switch (event.type)
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_running = false;
					break;
				case SDLK_LEFT:
					if (m_activeCount == 30)
					{
						m_nextCount = 1000; m_activeNPCCount = 500;
					}
					else if (m_activeCount == 100)
					{
						m_nextCount = 30; m_activeNPCCount = 5;
					}
					else if (m_activeCount == 1000)
					{
						m_nextCount = 100; m_activeNPCCount = 50;
					}
					break;
				case SDLK_RIGHT:
					if (m_activeCount == 30)
					{
						m_nextCount = 100; m_activeNPCCount = 50;
					}
					else if (m_activeCount == 100)
					{
						m_nextCount = 1000; m_activeNPCCount = 500;
					}
					else if (m_activeCount == 1000)
					{
						m_nextCount = 30; m_activeNPCCount = 5;
					}
					break;
				default:
					SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
					break;
				}
		}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::UnloadContent()
{
	DEBUG_MSG("Unloading Content");
	delete(m_p_Texture);
	m_p_Texture = NULL;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}
