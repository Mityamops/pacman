#pragma once
#include "Vector.h"
#include<vector>

class GameObject {
protected:
	std::vector<std::vector<int>>* map;
public:
	GameObject(std::vector<std::vector<int>>* map);
	virtual void Draw() = 0;
	//virtual void Read() = 0;
};
