#pragma once
#include"MovingObject.h"
#include"Vector.h"
class Pacman :public MovingObject {
private:
	int hp;
	
public:
	Pacman(std::vector<std::vector<int>>* map) ;
	void Draw() override;
	//virtual void Read() override {};
	void sumspeed(Vector v);
	void setspeed(float x, float y);
	Vector getpos();

};
