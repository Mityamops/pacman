#pragma once

#include"MovingObject.h"
#include<vector>

class Enemy :public MovingObject {
private:
	Vector StartPosEnemy;
	Vector rspeed = { 0,0 };
	std::vector<float> color;
public:
	//Enemy(std::vector<std::vector<int>>* map) : GameObject(map) { pos.setx(13); pos.sety(14); };
	Enemy(std::vector<std::vector<int>>* map, Vector Coord, std::vector<float> color);
	void Draw() override;
	//virtual void Read()override;
};

