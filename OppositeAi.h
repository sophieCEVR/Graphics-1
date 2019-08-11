#pragma once
#include "dumbAI.h"
class OppositeAi :
	public dumbAI
{
public:
	bool lead = false;
	OppositeAi();
	~OppositeAi();

	void additionalUpdate();
};

