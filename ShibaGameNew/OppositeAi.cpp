#include "OppositeAi.h"



OppositeAi::OppositeAi()
{
	Xchar = 350;						//starting x position for specified character
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
	textureFolder = "AI1";
	movementSpeed = 6;
}


OppositeAi::~OppositeAi()
{
}

void OppositeAi::additionalUpdate() {
	stepCounter = stepCounter + characterMovementSpeed;
	//if (Xchar < (Xobject -5)) {
	//	forward = false;
	//	backward = false;
	//	left = false;
	//	right = true;
	//	Xchar += movementSpeed;
	//}
	//else if (Xchar > (Xobject+5)) {
	//	forward = false;
	//	backward = false;
	//	left = true;
	//	right = false;
	//	Xchar -= movementSpeed;
	//}
	if (Ychar < Yobject) {
		if (distance > 300) {
			if (!collideUp) {
				forward = true;
				backward = false;
				left = false;
				right = false;
				Ychar += movementSpeed;
			}
			else if (!collideRight) {
				//if (collideLeft) {
				//	Xchar += 2;
				//}
				forward = false;
				backward = false;
				left = false;
				right = true;
				Xchar += movementSpeed;
			}
			else if (!collideDown) {
				//if (collideLeft) {
				//}
				additionalAIProcessing();
				forward = false;
				backward = true;
				left = false;
				right = false;
				Ychar -= movementSpeed;
			}
			else if (!collideLeft) {
				//if (collideUp) {
				//	Ychar -= 2;
				//}
				forward = false;
				backward = false;
				left = true;
				right = false;
				Xchar -= movementSpeed;
			}
			else {
				forward = true;
				backward = false;
				left = false;
				right = false;
			}
		}
		else {
			if (Xchar < (Xobject - 5)) {
				forward = false;
				backward = false;
				left = false;
				right = true;
				Xchar += movementSpeed;
			}
			else if (Xchar >(Xobject + 5)) {
				forward = false;
				backward = false;
				left = true;
				right = false;
				Xchar -= movementSpeed;
			}
			else if (Ychar > Yobject) {
				forward = false;
				backward = true;
				left = false;
				right = false;
				Ychar -= movementSpeed;
			}
			else if (Ychar < Yobject) {
				forward = false;
				backward = true;
				left = false;
				right = false;
				Ychar += movementSpeed;
			}
		}

	}

}