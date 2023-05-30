#include "Vector.h"
#include <GL\glut.h>
Vector::Vector()
{
	this->xc = 0;
	this->yc = 0;
}

Vector::Vector(float x, float y)
{
	this->xc = x;
	this->yc = y;
}

void Vector::setx(float x) {
	xc = x;
}
void Vector::sety(float y) {
	yc = y;
}

float Vector::getx() {
	return xc;
}
float Vector::gety() {
	return yc;
}
void Vector::DrawVector() {
glVertex2f(xc, yc);
}
Vector Vector::transformation() {
	Vector newCoord;
	float dx = 8.f / 224, dy = 8.f / 288;
	newCoord.setx(xc / 14 - 1 + dx);
	newCoord.sety(1 - yc / 18 - dy);
	return newCoord;
}

void Vector::operator= (const Vector& other) {
	this->xc = other.xc;
	this->yc = other.yc;

}
Vector Vector::operator+ (const Vector& other) {
	this->xc += other.xc;
	this->yc += other.yc;
	return Vector{ this->xc += other.xc,
	this->yc += other.yc };
}
Vector Vector::operator- (const Vector& other) {
	return Vector{ this->xc -= other.xc,
	this->yc -= other.yc };
}
void Vector::operator+= (const Vector& other) {
	this->xc += other.xc;
	this->yc += other.yc;

}
void Vector::operator-= (const Vector& other) {
	this->xc -= other.xc;
	this->yc -= other.yc;
}
void Vector::operator*=(const float mul) {
	xc *= mul;
	yc *= mul;
}
bool Vector::operator==(Vector other) {
	if (other.getx() == this->xc && other.gety() == this->yc)
		return true;
	else
		return false;
}

