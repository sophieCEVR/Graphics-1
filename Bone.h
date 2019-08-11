#pragma once
#include "Item.h"
class Bone :
	public Item
{
public:
	Bone(int i, int y, GLuint texture);
	~Bone();
	//void init();
};

