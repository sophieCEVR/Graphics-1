#include "Heart.h"

Heart::Heart(int i, int y, GLuint texture) : Item(i, y, texture) {}

Heart::~Heart() {
	itemTexture = 0;
	width = 0;
	height = 0;
}

//void Heart::init() {
//	xItem = tileWidth * xPosition;
//	yItem = tileHeight * yPosition;
//}