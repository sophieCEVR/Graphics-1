#pragma once
#include "Item.h"
class Chicken :
	public Item
{
public:
	Chicken(int i, int y, GLuint texture);
	~Chicken();
	void init();
};

