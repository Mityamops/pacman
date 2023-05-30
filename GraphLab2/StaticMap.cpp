#include "StaticMap.h"
#include <GL\glut.h>
#include<vector>


void PaintWall(float a, float b) {
	
	Vector Coord = { a,b };
	Vector NewCoord = Coord.transformation();
	float dx = 6.f/224, dy = 6.f / 288;
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(0.0f, 0.0f, 1.0f);

	glVertex2f(NewCoord.getx()-dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() + dy);
	glVertex2f(NewCoord.getx() - dx, NewCoord.gety() + dy);

	glEnd();

}

void DrawEmerald(Vector Coord) {
	Vector pos = Coord.transformation();
	glColor3f(1, 1, 1);    glBegin(GL_POLYGON);
	glVertex2f(pos.getx() - 3.f/224*3, pos.gety());    glVertex2f(pos.getx() - 1.5 / 224*3, pos.gety() + 1.5 / 288*3);
	glVertex2f(pos.getx() - 0.5 / 224*3, pos.gety() + 1.5/288*3);    glVertex2f(pos.getx() - 1.5 / 224*3, pos.gety());
	glEnd();
	glColor3f(1, 1, 0);    glBegin(GL_POLYGON);
	glVertex2f(pos.getx() - 1.5 / 224*3, pos.gety());    glVertex2f(pos.getx() - 0.5 / 224*3, pos.gety() + 1.5 /288*3);
	glVertex2f(pos.getx() + 0.5 / 224*3, pos.gety() + 1.5 /288*3);    glVertex2f(pos.getx() + 1.5 / 224*3, pos.gety());
	glEnd();
	glColor3f(0, 1, 0);    glBegin(GL_POLYGON);
	glVertex2f(pos.getx() + 1.5 / 224*3, pos.gety());    glVertex2f(pos.getx() + 0.5 / 224*3, pos.gety() + 1.5 /288*3);
	glVertex2f(pos.getx() + 1.5 / 224*3, pos.gety() + 1.5 /288*3);    glVertex2f(pos.getx() + 3.f/224*3, pos.gety());
	glEnd();
	glColor3f(1, 1, 0);    glBegin(GL_POLYGON);
	glVertex2f(pos.getx() - 3.f/224*3, pos.gety());    glVertex2f(pos.getx() - 1.5 / 224*3, pos.gety());
	glVertex2f(pos.getx(), pos.gety() - 3.f/288*3);
	glEnd();
	glColor3f(0, 1, 0);    glBegin(GL_POLYGON);
	glVertex2f(pos.getx() - 1.5 / 224*3, pos.gety());    glVertex2f(pos.getx() + 1.5 / 224*3, pos.gety());
	glVertex2f(pos.getx(), pos.gety() - 3.f /288*3);    glEnd();
	glColor3f(0, 0.5, 0);
	glBegin(GL_POLYGON);    glVertex2f(pos.getx() + 1.5 / 224*3, pos.gety());
	glVertex2f(pos.getx() + 3.f/224*3, pos.gety());    glVertex2f(pos.getx(), pos.gety() - 3.f / 288 *3);
	glEnd();
};

void PaintDot(float a, float b) {

	Vector Coord = { a,b };
	Vector NewCoord = Coord.transformation();
	float dx = 2.f/224, dy = 2.f /288;
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex2f(NewCoord.getx() - dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() + dy);
	glVertex2f(NewCoord.getx() - dx, NewCoord.gety() + dy);

	glEnd();


}
void PaintBigDot(float a, float b) {

	Vector Coord = { a,b };
	/*Vector NewCoord = Coord.transformation();
	float dx = 5.f/224, dy = 5.f / 288;
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(1.0f, 0.5f, 1.0f);

	glVertex2f(NewCoord.getx() - dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() + dy);
	glVertex2f(NewCoord.getx() - dx, NewCoord.gety() + dy);

	glEnd();*/
	DrawEmerald(Coord);
}


void PaintDoors(float a,float b){


	Vector Coord = { a,b };
	Vector NewCoord = Coord.transformation();
	float dx = 8.f / 224, dy = 2.f / 288;
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex2f(NewCoord.getx() - dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() - dy);
	glVertex2f(NewCoord.getx() + dx, NewCoord.gety() + dy);
	glVertex2f(NewCoord.getx() - dx, NewCoord.gety() + dy);

	glEnd();



}

void StaticMap::Draw() {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 28; j++) {
			int a = map->at(i).at(j);

			if(a==1)
				PaintWall(j, i);
			if (a == 2)
				PaintDot(j, i);
			if (a == 3)
				PaintBigDot(j, i);
			if (a == 4)
				PaintBigDot(j, i);
			if (a == 8)
				PaintDoors(j, i);
		}
	}
	
}