#include "Pacman.h"
#include <GL\glut.h>
#include"MovingObject.h"
#include<cmath>
#include<vector>
#include<string>
#include"MoveObjFunc.h"
#define PI 3.14


std::vector<std::vector<int>> startmap ;

Pacman::Pacman(std::vector<std::vector<int>>* map) :MovingObject(map) {
	this->hp = 3;
	speed = Vector(0.005,0);
	for (int i = 0; i < 36; i++) {
		std::vector<int> v;
		for (int j = 0; j < 28; j++) {
			v.push_back(map->at(i).at(j));
			if (map->at(i).at(j) == 4){
				pos.setx(j);
				pos.sety(i);
				StartPos = pos;
              }
		}
		startmap.push_back(v);
	}
	

}

void Pacman::sumspeed(Vector v) {
	speed += v;
}
void Pacman::setspeed(float x, float y) {
	speed.setx(x);
	speed.sety(y);
}
Vector Pacman:: getpos() {
	return pos;
}




int MouthMove = 0;
Vector RealSpeed = { 0,0 };
int counter = 0;
int CounterOfDot = 0;
int ready = 5000;
void Move(Vector pos,std::vector<std::vector<int>>* map, Vector speed) {
	
		int a = map->at((int)pos.gety()).at((int)(pos.getx() + 1));
		int b = map->at((int)pos.gety()).at((int)(pos.getx() - 1));
		int c = map->at((int)(pos.gety() + 1)).at((int)pos.getx());
		int d = map->at((int)(pos.gety() - 1)).at((int)pos.getx());

		if (//мен€ю скорость пакмана если по направлению скорости нет стен
			(speed.getx() > 0 && a != 1)
			|| (speed.getx() < 0 && b != 1)
			|| (speed.gety() > 0 && c != 1)
			|| (speed.gety() < 0 && d != 1))
			RealSpeed = speed;
		if (//если по направлению движени€ в след клетке есть стена то пакман останавливаетс€
			((RealSpeed.getx() > 0) && (a == 1))
			|| ((RealSpeed.getx() < 0) && (b == 1))
			|| ((RealSpeed.gety() > 0) && (c == 1))
			|| ((RealSpeed.gety() < 0) && (d == 1))) {
			RealSpeed.setx(0);
			RealSpeed.sety(0);
		}

		if (map->at((int)pos.gety()).at((int)pos.getx()) == 2) {//пакман ест еду
			map->at((int)pos.gety()).at((int)pos.getx()) = 0;
			counter += 10;
			CounterOfDot++;
		}
		if (map->at((int)pos.gety()).at((int)pos.getx()) == 3) {
			map->at((int)pos.gety()).at((int)pos.getx()) = 0;
			counter += 50;	
			map->at(0).at(1) = 5;
		}
	
}
void DrawPacMan(Vector pos,Vector speed) {
	float x, y;
	float cnt = 40;
	float RadiusX = 10.f / 224;//полуоси по х 
	float RadiusY = 10.f / 288;// и y  пакмана
	float a = 3.1415 * 2 / cnt;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 0);
	glVertex2f(pos.transformation().getx(), pos.transformation().gety());
	for (int i = -1; i < cnt; i++) {//рисует тело пакмана
		x = pos.transformation().getx() + sin(a * i) * RadiusX;
		y = pos.transformation().gety() + cos(a * i) * RadiusY;
		glVertex2f(x, y);
	}
	glEnd();

	MouthMove += 10;

	if (MouthMove > 20) {//рисует рот пакмана
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0, 0, 0);
		glVertex2f(pos.transformation().getx(), pos.transformation().gety());
		float alpha = 0;
		if (RealSpeed.getx() > 0) {
			alpha = PI / 4;
		}
		if (RealSpeed.getx() < 0) {
			alpha = 5 * PI / 4;
		}
		if (RealSpeed.gety() > 0) {
			alpha = 7 * PI / 4;
		}
		if (RealSpeed.gety() < 0) {
			alpha = 3 * PI / 4;
		}
		if (RealSpeed.getx() == 0 && RealSpeed.gety() == 0) {
			if (speed.getx() > 0) {
				alpha = PI / 4;
			}
			if (speed.getx() < 0) {
				alpha = 5 * PI / 4;
			}
			if (speed.gety() > 0) {
				alpha = 7 * PI / 4;
			}
			if (speed.gety() < 0) {
				alpha = 3 * PI / 4;
			}
		}
		glVertex2f(pos.transformation().getx() + RadiusX * cos(alpha) / cos(PI / 4), pos.transformation().gety() + RadiusY * sin(alpha) / cos(PI / 4));
		glVertex2f(pos.transformation().getx() + RadiusX * cos(-PI / 2 + alpha) / cos(PI / 4), pos.transformation().gety() + RadiusY * sin(-PI / 2 + alpha) / cos(PI / 4));
		MouthMove -= 16;
	};

	glEnd();

}
void DrawHeart(Vector Coord) {
	float cnt = 40;
	float a = 2 * PI / cnt;
	float x, y;
	float RadiusX = 0.7 / 224;//полуоси по х 
	float RadiusY = 1.f / 288;//полуоси по y
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2f(Coord.transformation().getx(), Coord.transformation().gety());
	for (int t = 0; t < cnt; t++) {
		x = 16 * pow(sin(t * a), 3)*RadiusY;
		y = (13 * cos(t * a) - 5 * cos(2 * t * a) - 2 * cos(3 * t * a) - cos(4 * t * a)) * RadiusX;
		glVertex2f(Coord.transformation().getx() + x, Coord.transformation().gety() + y);

	}
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	float dX = 5.f / 224, dY = 5.f / 288;
	float blick_X = Coord.transformation().getx()+dX, blick_Y = Coord.transformation().gety()+dY;
	float dx = 1.5 / 224, dy = 1.5 / 288;
	glVertex2f(blick_X+dx, blick_Y+dy);
	glVertex2f(blick_X + dx, blick_Y - dy);
	glVertex2f(blick_X - dx, blick_Y - dy);
	glVertex2f(blick_X - dx, blick_Y + dy);
	glEnd();

}
void Trace(std::vector<std::vector<int>>* map, Vector pos) {
	if (ready == 0) {
		if (RealSpeed.getx() > 0) {//оставл€ет след
			map->at((int)pos.gety()).at((int)pos.getx() - 1) = 0;
		}
		if (RealSpeed.getx() < 0) {
			map->at((int)pos.gety()).at((int)pos.getx() + 1) = 0;
		}
		if (RealSpeed.gety() > 0) {
			map->at((int)pos.gety() - 1).at((int)pos.getx()) = 0;
		}
		if (RealSpeed.gety() < 0) {
			map->at((int)pos.gety() + 1).at((int)pos.getx()) = 0;
		}
	}
}


int DoorTime1 = 20000;
int DoorTime2 = 30000;
int DoorTime3= 40000;
bool isGameOverforPacman = false;
int level = 1;


void Door(std::vector<std::vector<int>>* map) {
	DoorTime1 -= 1;
	DoorTime2 -= 1;
	DoorTime3 -= 1;

	if (DoorTime1 == 3000) {
		map->at(15).at(12) = 0;

	}


	if (DoorTime2 == 3000) {
		map->at(15).at(14) = 0;

	}

	if (DoorTime3 == 3000) {
		map->at(15).at(16) = 0;

	}


	if (DoorTime1 == 2999) {
		map->at(15).at(12) = 8;
	}
	if (DoorTime2 == 2999) {
		map->at(15).at(14) = 8;
	}
	if (DoorTime3 == 2999) {
		map->at(15).at(16) = 8;
	}

}

void Writing(std::vector<std::vector<int>> * map,int hp) {
	if (ready > 0) {//отрисовка надписи реди в начале игры
		map->at(20).at(11) = 6;
		renderBitmapString({ 11,20 }, "READY!");
		ready -= 1;

	}
	if (hp <= 0)
		renderBitmapString({ 10, 18 }, "GAME OVER");//если жизни закончиилсь то гейм овер


	if (hp > 0)
		DrawHeart({ 9,34 });
	if (hp > 1)
		DrawHeart({ 7,34 });
	if (hp > 2)
		DrawHeart({ 5,34 });

	renderBitmapString({ 3,2 }, std::to_string(counter));
	renderBitmapString({ 10,2 }, "level");
	renderBitmapString({ 15,2 }, std::to_string(level));


}

void PacmanMove(Vector* pos, std::vector<std::vector<int>>* map,Vector* speed) {
	if (IntCheck(*pos) && (*pos).getx() < 27 && (*pos).getx() > 0 && isGameOverforPacman == false) {//проверка стоит ли пакман в поле с целым значеним
		(*pos).setx(round((*pos).getx()));//доводка пакмана до целого пол€ (нужно дл€ корректировки ошибки машинной погрешности)
		(*pos).sety(round((*pos).gety()));

		Trace(map, *pos);//убирает точки за собой
		Move(*pos, map, *speed);//движение	
		map->at((int)(*pos).gety()).at((int)(*pos).getx()) = 4;//оставл€ет хитбокс по которому призраки наход€т пакмана

	}
}

void LifeProcessing(Vector* pos, std::vector<std::vector<int>>* map, int* hp,Vector StartPos){
	if (map->at(0).at(0) == 5) {//пакман тер€ет жизнь когда его сьедают
		if (ready == 0)
			*hp -= 1;
		RealSpeed.setx(0);
		RealSpeed.sety(0);
		if (*hp > 0) {

			map->at((int)(*pos).gety()).at((int)(*pos).getx()) = 0;//убирает хитбокс с места смерти
			*pos = StartPos;
			ready = 5000;
			DoorTime1 = 10000;
			DoorTime2 = 20000;
			DoorTime3 = 30000;
		}
	}
}



void LevelProcessing(Vector* pos, std::vector<std::vector<int>>* map, Vector* speed,Vector StartPos) {
	if (CounterOfDot < 240) {
		DrawPacMan(*pos, *speed);
	}
	else {//обработка конца уровн€
		for (int i = 0; i < 36; i++) {
			for (int j = 0; j < 28; j++) {
				map->at(i).at(j) = startmap[i][j];
			}
		}
		DoorTime1 = 10000;
		DoorTime2 = 20000;
		DoorTime3 = 30000;

		CounterOfDot = 0;
		ready = 5000;
		*pos = StartPos;
		level += 1;
		map->at(0).at(2) = 10;//флаг дл€ перехода на новый уровень
	}

}

void Pacman::Draw(){
	map->at(0).at(1) = 0;//убираю флаг дл€ режима берсерка
	map->at(0).at(2) = 0;

	Writing(map, hp);// отрисовка всех надписей и сердец
	
	Door(map);//открывание и закрывание двери
	
	PacmanMove(&pos, map,&speed);// движение пакмана

	LifeProcessing(&pos, map, &hp,StartPos); //обработка жизней
	
	 
	Teleport(&pos, map);//телепорт через боковые клетки


	if (ready == 0) {
		pos += RealSpeed;
		map->at(20).at(11) = 0;//убирает надпись реди
	}

	LevelProcessing(&pos, map, &speed, StartPos);
	
	
}
