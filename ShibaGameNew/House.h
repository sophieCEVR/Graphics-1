#pragma once
#include "MapObject.h"
#include "Map.h"

class House :
	public MapObject
{
public:
	House(int xPosition, int yPosition, GLuint texture);
	~House();
	void init();
};

