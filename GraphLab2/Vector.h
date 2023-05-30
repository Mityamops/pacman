#pragma once
class Vector
{
private:
	float xc , yc ;
public:
	Vector();
	Vector(float x, float y);
	void setx(float x);
	void sety(float y);
	float getx();
	float gety();
	void DrawVector();
	Vector transformation();

	void operator= (const Vector& other);
	Vector operator+ (const Vector& other);
	Vector operator- (const Vector& other);
	void operator+= (const Vector& other);
	void operator-= (const Vector& other);
	void operator*=(const float mul);
	bool operator==(Vector other);
};

