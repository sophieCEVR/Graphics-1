#include "House.h"



House::House(int xPosition, int yPosition, GLuint texture) : MapObject(xPosition, yPosition, texture) {}
//{
//	objTexture = texture;
//	width = 8;
//	height = 8;
//	xObj = tileWidth*xPosition;
//	yObj = tileHeight*yPosition;
//}


House::~House(){}

void House::init() {
	width = 8;
	height = 8;
}
