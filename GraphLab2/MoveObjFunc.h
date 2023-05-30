#include<string>
#include"Vector.h"
#include<vector>
#pragma once

bool IntCheck(Vector coord);

void renderBitmapString(Vector Coord, std::string str);

void Teleport(Vector* pos, std::vector<std::vector<int>>* map);