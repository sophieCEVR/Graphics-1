#pragma once
#include "MapObject.h"
class MiniGameBarn :
	public MapObject
{
public:
	OBB mgOBB;							//allows for use of oriented bounding box collision detection
	float objectMatrix[16];
	GLuint textureOpen = 0;
	MiniGameBarn(int xPosition, int yPosition, GLuint texture);
	~MiniGameBarn();
	void importOpenTexture(GLuint textureClosed);
	void init();
	void additionalDisplay();
};

