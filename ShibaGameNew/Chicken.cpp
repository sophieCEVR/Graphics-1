#include "Chicken.h"

Chicken::Chicken(int i, int y, GLuint texture) : Item(i, y, texture) {}

Chicken::~Chicken() {}

void Chicken::init() {
	width = 3;
	height = 3;
}
