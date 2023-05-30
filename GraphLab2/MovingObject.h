#include"GameObject.h"
#pragma once
class MovingObject:public GameObject
{
protected:
	Vector StartPos;
	Vector pos;
	Vector speed;
	
public:
	MovingObject(std::vector<std::vector<int>>* map) :GameObject(map) { speed.setx(0); speed.sety(0);};
};

