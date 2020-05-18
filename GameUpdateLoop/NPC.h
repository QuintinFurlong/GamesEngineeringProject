#ifndef NPC_H
#define NPC_H

#include "Vector2D.h"
#include <vector>
class NPC
{
public:
	NPC();
	~NPC();
	void setup(Vector2D t_pos, Vector2D t_goal);
	void pathFind();
	void update();
	Vector2D getPos();

	Vector2D m_pos, m_goal;
	std::vector<Vector2D> m_path;
};
#endif