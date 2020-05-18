#include "NPC.h"

NPC::NPC()
{

}

NPC::~NPC()
{
}

void NPC::setup(Vector2D t_pos, Vector2D t_goal)
{
	m_pos = t_pos;
	m_goal = t_goal;
}

void NPC::pathFind()
{
	//u know
}

void NPC::update()
{
	if (m_path.size() > 0)
	{
		m_pos = m_path.back();
		m_path.pop_back();
	}
}

Vector2D NPC::getPos()
{
	return m_pos;
}
