#include "dumbAI.h"



dumbAI::dumbAI()
{
	Xchar = 250;						//starting x position for specified character
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

void dumbAI::chickenLocation(int xPosition, int yPosition) {
	Xobject = xPosition;
	Yobject = yPosition;
}
dumbAI::~dumbAI(){}

void dumbAI::additionalDisplay()
{
	/**********************************************************************************************/
	//Lead Creation (backwards view) - ordering requires here
	/**********************************************************************************************/
	if (lead && backward) {
		glLineWidth(3.0);
		if (distance < 175) {
			glColor3f(1.0, 0.0, 0.0);
		}
		else {
			lead = false;
		}
		glBegin(GL_LINES);
		glVertex2f(Xchar, Ychar);
		glVertex2f(Xobject, Yobject);
		glEnd();
		glPopMatrix();
	}

	/**********************************************************************************************/
	//Lead Creation (all other views)
	/**********************************************************************************************/

	/************************************* Lead Creation ******************************************/

	if (lead && !backward) {
		glPushMatrix();
		glLineWidth(3.0);
		if (distance < 175) {
			glColor3f(1.0, 0.0, 0.0);
		}
		else {
			lead = false;
		}
		glBegin(GL_LINES);
		glVertex2f(Xchar, Ychar);
		glVertex2f(Xobject, Yobject);
		glEnd();
		glPopMatrix();
	}

	/**************************************** Lead Tie ********************************************/

	glPushMatrix();
	glTranslatef(Xobject, Yobject, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEnd();
	glPointSize(1.0);

	glPopMatrix();

	/**********************************************************************************************/
	//OBB for all directions
	/**********************************************************************************************/

	if (forward || backward) {
		charOBB.vertOriginal[0].x = -Xfb1;
		charOBB.vertOriginal[0].y = -Yfb1;

		charOBB.vertOriginal[1].x = -Xfb2;
		charOBB.vertOriginal[1].y = Yfb2;

		charOBB.vertOriginal[2].x = Xfb2;
		charOBB.vertOriginal[2].y = Yfb2;

		charOBB.vertOriginal[3].x = Xfb1;
		charOBB.vertOriginal[3].y = -Yfb1;
	}
	else {
		charOBB.vertOriginal[0].x = -Xlr1;
		charOBB.vertOriginal[0].y = -Ylr1;

		charOBB.vertOriginal[1].x = -Xlr1;
		charOBB.vertOriginal[1].y = Ylr2;

		charOBB.vertOriginal[2].x = Xlr2;
		charOBB.vertOriginal[2].y = Ylr2;

		charOBB.vertOriginal[3].x = Xlr2;
		charOBB.vertOriginal[3].y = -Ylr1;
	}
}

void dumbAI::processKeys() {}

void dumbAI::additionalUpdate(){
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
	if (!lead) {
		if (Ychar < Yobject) {
			if (distance > 300) {
				if (!collideUp) {
					forward = true;
					backward = false;
					left = false;
					right = false;
					Ychar += movementSpeed;
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
				else if (Xchar > (Xobject + 5)) {
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
	
}

void dumbAI::additionalAIProcessing() {}