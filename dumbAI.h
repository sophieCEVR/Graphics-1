#pragma once
#include "Character.h"
class dumbAI :
	public Character
{
public:
	int i = 1;
	bool lead = false;
	dumbAI();
	~dumbAI();
	void processKeys();		//allows for processing of key presses
	//GLuint loadPNG(char* name);			//allows for texture loading 
//	virtual void init();
	virtual void additionalUpdate();
	void chickenLocation(int xPosition, int yPosition);
	void additionalDisplay();
	virtual void additionalAIProcessing();
};

