#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
	void LoadContent();
	void UnloadContent();
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
private:
	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Texture* m_p_Texture;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
	SDL_Surface* m_p_Surface;

	static const int MAX = 1000;
	SDL_Rect m_block[MAX][MAX];
	int m_activeCount, m_nextCount;
	static const int MAX_NPC = 500;
	SDL_Rect m_npc[MAX_NPC];
	int m_activeNPCCount;
};
#endif

