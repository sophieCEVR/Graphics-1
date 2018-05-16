#pragma once
#include "MapObject.h"
class CornerPath :
	public MapObject
{
public:

	//OBB declaration
	OBB pathOBB;							//allows for use of oriented bounding box collision detection
	float objectMatrix[16];
	char charPassed = ' ';
	CornerPath(char charPassed, int xPosition, int yPosition, GLuint texture);
	~CornerPath();
	void additionalDisplay();
	void init();
};

