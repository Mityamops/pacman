#pragma once
#include"GameObject.h"
#include"Vector.h"

class StaticMap :public GameObject {
private:
	
public:
	StaticMap(std::vector<std::vector<int>>* map) : GameObject(map) {};
	void Draw() override;
	//virtual void Read()override;
};