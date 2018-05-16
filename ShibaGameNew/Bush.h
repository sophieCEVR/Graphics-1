#pragma once
#include "MapObject.h"
class Bush :
	public MapObject
{
public:
	Bush( int xPosition, int yPosition, GLuint texture);
	~Bush();
};

