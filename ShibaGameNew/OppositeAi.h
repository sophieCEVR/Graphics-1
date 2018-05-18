#pragma once
#include "dumbAI.h"
class OppositeAi :
	public dumbAI
{
public:
	OppositeAi();
	~OppositeAi();

	void additionalUpdate();
};

