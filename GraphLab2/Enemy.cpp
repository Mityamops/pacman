#include "Enemy.h"
#include"MovingObject.h"
#include <GL\glut.h>
#include"Vector.h"
#include<string>
#include <time.h>
#include<random>
#include"MoveObjFunc.h"
#define PI 3.1415

float lvlStep = 0.005
;
float Step = lvlStep;
float LowStep = lvlStep / 2;
Enemy::Enemy(std::vector<std::vector<int>>* map, Vector Coord,std::vector<float> color) :MovingObject(map) {
	
	
	speed = Vector(0, -lvlStep);
	pos.setx(Coord.getx());
	pos.sety(Coord.gety());
	StartPos = pos;

	this->color = color;
}

int LegsMove=0;


void DrawCircle(Vector Coord,float radius,std::vector<float> rgb) {
	float x, y;
	float cnt = 40;
	float a = (PI*2) / cnt;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(rgb.at(0), rgb.at(1), rgb.at(2));
	glVertex2f(Coord.transformation().getx(), Coord.transformation().gety());
	for (int i = 0; i <= cnt; i++) {//рисует тело приведения	
		x = Coord.transformation().getx() + cos(a * i) * radius;
		y = Coord.transformation().gety() + sin(a * i) * radius;
		glVertex2f(x, y);


	}
	glEnd();



}

void DrawSemiCircle(Vector Coord, float radius, std::vector<float> rgb) {
	float x, y;
	float cnt = 40;
	//float RadiusX = 10.f / 224;
	float a = (PI + 0.1) / cnt;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(rgb.at(0), rgb.at(1), rgb.at(2));
	glVertex2f(Coord.transformation().getx(), Coord.transformation().gety());
	for (int i = -1; i < cnt; i++) {//рисует тело приведения	
		x = Coord.transformation().getx() + cos(a * i) * radius;
		y = Coord.transformation().gety() + sin(a * i) * radius;
		glVertex2f(x, y);


	}
	glEnd();


}

void DrawLegs(Vector Coord, float radius,std::vector<float> rgb) {
	LegsMove += 10;
	glBegin(GL_TRIANGLES);
	glColor3f(rgb.at(0), rgb.at(1), rgb.at(2));


	glVertex2f(Coord.transformation().getx()-radius, Coord.transformation().gety());
	if(LegsMove<20)
		glVertex2f(Coord.transformation().getx() - radius, Coord.transformation().gety()-radius);
	else
		glVertex2f(Coord.transformation().getx() - radius/2, Coord.transformation().gety() - radius);
	glVertex2f(Coord.transformation().getx() - radius/2, Coord.transformation().gety());
	 


	glVertex2f(Coord.transformation().getx(), Coord.transformation().gety());
	if (LegsMove<20)
		glVertex2f(Coord.transformation().getx(), Coord.transformation().gety() - radius);
	else
		glVertex2f(Coord.transformation().getx()-radius/2, Coord.transformation().gety() - radius);
	glVertex2f(Coord.transformation().getx() - radius / 2, Coord.transformation().gety());



	glVertex2f(Coord.transformation().getx() + radius, Coord.transformation().gety());
	if(LegsMove<20)
		glVertex2f(Coord.transformation().getx() + radius, Coord.transformation().gety() - radius);
	else
		glVertex2f(Coord.transformation().getx() + radius/2, Coord.transformation().gety() - radius);
	glVertex2f(Coord.transformation().getx() + radius / 2, Coord.transformation().gety());



	glVertex2f(Coord.transformation().getx(), Coord.transformation().gety());
	if(LegsMove<20)
	glVertex2f(Coord.transformation().getx(), Coord.transformation().gety() - radius);
	else {
		glVertex2f(Coord.transformation().getx() + radius / 2, Coord.transformation().gety() - radius);
		LegsMove -= 14;
	}
	glVertex2f(Coord.transformation().getx() + radius / 2, Coord.transformation().gety());


	glEnd();

}

void DrawEnemy(Vector pos, Vector speed,std::vector<float>color) {
	float RadiusBody = 10.f / 224;
	DrawSemiCircle(pos,RadiusBody,color);
	float RadiusEye = 3.5 / 224;
	float dx = 75.f / 224;
	float dy = 75.f / 288;
	

	float dxPupil = 0;
	float dyPupil = 0;
	if (speed.getx() > 0)
		dxPupil = 10.f / 224;
	if (speed.getx() < 0)
		dxPupil = -10.f / 224;
	if (speed.gety() < 0)
		dyPupil = 15.f / 224;
	if (speed.gety() > 0)
		dyPupil = -15.f / 224;

	Vector LeftEye = {pos.getx()- dx,pos.gety() - dy };
	Vector RightEye = { pos.getx() + dx,pos.gety() -dy };
	Vector LeftPupil = { pos.getx() - dx+dxPupil,pos.gety() - dy - dyPupil };
	Vector RightPupil = { pos.getx() + dx+dxPupil,pos.gety() - dy - dyPupil };
	float RadiusPupil = 2.5 / 224;
	//глаза
	DrawCircle(LeftEye, RadiusEye, {1,1,1});
	DrawCircle(RightEye, RadiusEye, { 1,1,1 });
	//зрачки
	DrawCircle(LeftPupil, RadiusPupil, { 0,0,1 });
	DrawCircle(RightPupil, RadiusPupil, { 0,0,1 });
	//ножки 
	DrawLegs(pos,RadiusBody,color);
	



}

int Random(std::vector<bool> r) {

	srand(time(NULL));
	std::vector<int> true_r;
	for (int i = 0; i < r.size();i++) {
		if (r.at(i) == true) {
			true_r.push_back(i);
		}
	}
	int RandomNumber = rand() % (true_r.size() );
	
	return true_r.at(RandomNumber);
	
}

int WallNearby(Vector pos, std::vector<std::vector<int>>* map,Vector Realspeed) {
	int a = map->at((int)pos.gety()).at((int)pos.getx() + 1);
	int b = map->at((int)pos.gety()).at((int)pos.getx() - 1);
	int c = map->at((int)pos.gety() + 1).at((int)pos.getx());
	int d = map->at((int)pos.gety() - 1).at((int)pos.getx());


	//если у призрака по направлению движения нет стены,то призрак идет прямо
	if ((Realspeed.getx() > 0) && c==1 &&d==1) {
		return -1;
	}
	if ((Realspeed.getx() < 0) && c==1 && d==1 ) {
		return -1;
	}
	if ((Realspeed.gety() > 0) && a==1 && b==1) {
		return -1;
	}
	if ((Realspeed.gety() < 0) && a == 1 && b == 1) {
		return -1;
	}
	

	bool up = true, down = true, left = true, right = true;
	//если с какой то стороны есть стена или призрак пришел с противоположной стороны , то ставим метку
	if (a==1||Realspeed.getx()<0||a==8)
		right=false;
	if (b==1 || Realspeed.getx() > 0 || b == 8)
		left=false;
	if (c==1 || Realspeed.gety() < 0 ||c == 8)
		up = false;
	if (d==1 || Realspeed.gety() > 0 || d == 8)
		down = false;

	std::vector<bool> sides{ left, up, right, down };
	
	int RandNumber =0;
	do
		RandNumber = Random(sides);
	while (sides.at(RandNumber) == false);
	return RandNumber;



}

bool GameOver = false;
int CounterGhosts = 0;

int TimerBerserk = 0;
int FullTimeBerserk = 20000;

void GameOverProcessing(Vector* rspeed,Vector* pos,Vector* StartPos, std::vector<std::vector<int>>* map) {
	if (GameOver) {
		(*rspeed).setx(0);
		(*rspeed).sety(0);
		*pos = *StartPos;
		CounterGhosts++;
	}

	if (CounterGhosts == 4) {
		GameOver = false;
		map->at(0).at(0) = 0;
		CounterGhosts = 0;
	}

	//проверка сьел ли пакмана
	if (map->at((int)(*pos).gety()).at((int)(*pos).getx()) == 4) {
		if (TimerBerserk > 0) {
			*pos = *StartPos;

		}
		else {
			GameOver = true;
			map->at(0).at(0) = 5;//ставлю флаг для проверки в pacman.cpp
			map->at((int)(*pos).gety()).at((int)(*pos).getx()) = 0;
		}

	}

}

void MoveProcessing(Vector* pos, std::vector<std::vector<int>>* map, Vector* speed, Vector* StartPos,Vector* rspeed) {


	if (map->at((int)(*pos).gety() - 1).at((int)(*pos).getx()) == 8)// двери
		*rspeed = Vector(0, 0);
	else {
		
		GameOverProcessing(rspeed, pos, StartPos, map);


		if (IntCheck(*pos) && (*pos).getx() < 27 && (*pos).getx() > 0) {//проверка стоит ли призрак в поле с целым значеним

			(*pos).setx(round((*pos).getx()));//доводка призрака до целого поля (нужно для корректировки ошибки машинной погрешности)
			(*pos).sety(round((*pos).gety()));

			if (*pos == *StartPos) {
				*speed = Vector(0, -Step);
			}
			else {
				int side = WallNearby(*pos, map, *speed);//алгоритм движения

				if (side == 0)
					*speed = Vector(-Step, 0);
				if (side == 1)
					*speed = Vector(0, Step);
				if (side == 2)
					*speed = Vector(Step, 0);
				if (side == 3)
					*speed = Vector(0, -Step);
			}
			*rspeed = *speed;

		}
	}

}

void EnergizerProcessing(Vector* pos,Vector* speed,std::vector<float> color) {
	std::vector <float> BlueColor = { 0,0,1 };
	if (TimerBerserk > 0) {// синие призраки если пакман сьел энерджайзер
		DrawEnemy(*pos, *speed, BlueColor);
		TimerBerserk -= 1;
		Step = LowStep;
	}
	else {
		DrawEnemy(*pos, *speed, color);
		Step = lvlStep;
	}

}



void Enemy::Draw() {
	
	if (map->at(0).at(1) == 5) {//обработка режима берсерка
		TimerBerserk = FullTimeBerserk;
	}
	if (map->at(0).at(2) == 10) {//обработка перехода на уровень
		FullTimeBerserk -= 125;
		
	}


	MoveProcessing(&pos,map,&speed,&StartPos,&rspeed);//обработка движения и окончания игры
	

	if (map->at(20).at(11) == 6)//проверка начала игры
		pos = StartPos;
	else
		pos += rspeed;


	EnergizerProcessing(&pos, &speed, color);//обработка берсерк мода
	

	Teleport(&pos,map);

}