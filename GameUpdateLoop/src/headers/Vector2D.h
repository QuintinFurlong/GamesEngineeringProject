#ifndef VECTOR_H
#define VECTOR_H

class Vector2D
{
public:
	Vector2D(float x=0, float y=0);
	float GetX();
	float GetY();
	void SetX(float);
	void SetY(float);
private:
	float m_x;
	float m_y;
};
#endif
