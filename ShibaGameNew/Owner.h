#pragma once
#include "Character.h"
#include <list>
class Owner :
	public Character
{
public:

	//list<Node> openList;/*
	//list<Node> closedList;*/
	Owner();
	~Owner();
	void additionalDisplay();
	void init();
//	void aStar();

};
