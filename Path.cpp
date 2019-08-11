#include "Path.h"



Path::Path(int xPosition, int yPosition, GLuint texture) : MapObject(xPosition, yPosition, texture) {}
//{
	//randomizeMapObject = randomizeMap;
	//textureCount = 25;
	//textureSource = "textures/Path/";
	//objTexture = texture;

	//xObj = tileWidth * xPosition;
	//yObj = tileHeight * yPosition;
//}


Path::~Path()
{
}

void Path::init() {
	width = 1.05;
	height = 1.05;
}
