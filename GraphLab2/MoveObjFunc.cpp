#include"MoveObjFunc.h"
#include <GL\glut.h>
#include<vector>

bool IntCheck(Vector coord) {


	float epsilon = 0.0005;

	if (abs(coord.getx() - round(coord.getx())) < epsilon && abs(coord.gety() - round(coord.gety())) < epsilon) {

		return true;

	}
	else
		return false;

}



void renderBitmapString(Vector Coord, std::string str) {
	glColor3f(1.0f, 1.0f, 1.0f);

	glRasterPos2f(Coord.transformation().getx(), Coord.transformation().gety());
	for (auto c : str) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}


void Teleport(Vector* pos, std::vector<std::vector<int>>* map) {
	// телепорт через боковые стены
	if ((*pos).getx() > 26.5) {
		(*pos).setx(2);
		map->at(17).at(26) = 0;
	}
	else if ((*pos).getx() < 0.5) {
		(*pos).setx(26);
		map->at(17).at(1) = 0;
	}
}