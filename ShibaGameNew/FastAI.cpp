#include "FastAI.h"



FastAI::FastAI()
{
	Xchar = 200;						//starting x position for specified character
	Ychar = 150;					//starting y position for specified character
	Xobject = 200;					//starting x position for specified object/point (for distance calculations) //make this chicken
	Yobject = 150;					//starting y position for specified object/point (for distance calculations)
	Xfb1 = 22.5;							//X axis int #1 when facing forward/backwards
	Xfb2 = 22.5;							//X axis int #2 when facing forward/backwards
	Yfb1 = 40.5;							//y axis int #1 when facing forward/backwards
	Yfb2 = 22.5;							//y axis int #2 when facing forward/backwards
	Xlr1 = 32.5;							//X axis int #1 when facing left/right
	Xlr2 = 32.5;							//X axis int #2 when facing left/right
	Ylr1 = 38;							//y axis int #1 when facing left/right
	Ylr2 = 20;							//y axis int #2 when facing left/right
	textureFolder = "AI3";
	movementSpeed = 6.25;
}


FastAI::~FastAI()
{
}

void FastAI::additionalAIProcessing() {
	if (collideUp) {
		Ychar -= 2;
	}
}
