#pragma once
#include "MapObject.h"
class Path :
	public MapObject
{
public:

	Path(int xPosition, int yPosition, GLuint texture);
	~Path();
	void init();
};

