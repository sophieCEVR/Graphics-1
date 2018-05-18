#pragma once
#include "dumbAI.h"
class FastAI :
	public dumbAI
{
public:
	bool lead = false;
	FastAI();
	~FastAI();
	void additionalAIProcessing();
};

