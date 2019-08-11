#include "Hanzo.h"
using namespace std;

Hanzo::Hanzo() {
	Xchar = 300;						//starting x position for specified character
	Ychar = 150;					//starting y position for specified character
	Xobject = 200;					//starting x position for specified object/point (for distance calculations)
	Yobject = 150;					//starting y position for specified object/point (for distance calculations)
	Xfb1 = 22.5;							//X axis int #1 when facing forward/backwards
	Xfb2 = 22.5;							//X axis int #2 when facing forward/backwards
	Yfb1 = 40.5;							//y axis int #1 when facing forward/backwards
	Yfb2 = 22.5;							//y axis int #2 when facing forward/backwards
	Xlr1 = 32.5;							//X axis int #1 when facing left/right
	Xlr2 = 32.5;							//X axis int #2 when facing left/right
	Ylr1 = 38;							//y axis int #1 when facing left/right
	Ylr2 = 20;							//y axis int #2 when facing left/right
	textureFolder = "Shiba";
}

void Hanzo::additionalDisplay()
{
	/**********************************************************************************************/
						//Lead Creation (backwards view) - ordering requires here
	/**********************************************************************************************/
	if (lead && backward) {
		glLineWidth(3.0);
		if (distance < 175) {
			//glColor3f(1.0, 0.0, 0.0);
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

	//glPushMatrix();
	//glTranslatef(Xobject, Yobject, 0.0);
	//glColor3f(1.0, 1.0, 0.0);
	//glPointSize(20.0);
	//glBegin(GL_POINTS);
	//	glVertex2f(0, 0);
	//glEnd();
	//glPointSize(1.0);

	//glPopMatrix();

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

//
void Hanzo::additionalInit()
{

	//stunned

}
	////glClearColor(0.0, 0.5, 0.0, 0.0);

	///********************************shiba png loading**************************************/

	////shiba walking forward
	//f1 = loadPNG("textures/Shiba/f1.png");
	//f2 = loadPNG("textures/Shiba/f2.png");
	//f3 = loadPNG("textures/Shiba/f3.png");
	//f4 = loadPNG("textures/Shiba/f4.png");
	////shiba walking backwards
	//b1 = loadPNG("textures/Shiba/b1.png");
	//b2 = loadPNG("textures/Shiba/b2.png");
	//b3 = loadPNG("textures/Shiba/b3.png");
	//b4 = loadPNG("textures/Shiba/b4.png");
	////shiba walking left
	//l1 = loadPNG("textures/Shiba/l1.png");
	//l2 = loadPNG("textures/Shiba/l2.png");
	//l3 = loadPNG("textures/Shiba/l3.png");
	//l4 = loadPNG("textures/Shiba/l4.png");
	////shiba walking right
	//r1 = loadPNG("textures/Shiba/r1.png");
	//r2 = loadPNG("textures/Shiba/r2.png");
	//r3 = loadPNG("textures/Shiba/r3.png");
	//r4 = loadPNG("textures/Shiba/r4.png");

	///**********************************************************************************************/
	//											//OBB init
	///**********************************************************************************************/

	//	charOBB.vertOriginal[0].x = -Xfb1;
	//	charOBB.vertOriginal[0].y = -Yfb1;

	//	charOBB.vertOriginal[1].x = -Xfb2;
	//	charOBB.vertOriginal[1].y = Yfb2;

	//	charOBB.vertOriginal[2].x = Xfb2;
	//	charOBB.vertOriginal[2].y = Yfb2;

	//	charOBB.vertOriginal[3].x = Xfb1;
	//	charOBB.vertOriginal[3].y = -Yfb1;
//}

Hanzo::~Hanzo() {}

void Hanzo::additionalProcessKeys(bool keys[256]) {
	if (boostMeter == 3) {
		if (keys[VK_SPACE]) {
			spacePressed = true;
		}
	}
	if (spacePressed && !collisionBoost) {
		movementSpeed = 10;
		characterMovementSpeed = 1.8f;
	}	
	else if (spacePressed && collisionBoost) {
		movementSpeed = 0;
	}
	else {
		movementSpeed = 6;
	}
	if (lead && distance<160) {
		if (keys[leftPress])
		{
			if (!collideLeft) {
				Xchar -= movementSpeed;
			}
		}
		if (keys[rightPress])
		{
			if (!collideRight) {
				Xchar += movementSpeed;
			}
		}
		if (keys[upPress])
		{
			if (!collideUp) {
				Ychar += movementSpeed;
			}
		}
		if (keys[downPress])
		{
			if (!collideDown) {
				Ychar -= movementSpeed;
			}
		}
	}
	else if (lead && distance >= 160) {
		if (keys[leftPress])
		{
			if (!collideLeft) {
				Xchar -= 0.004f;
			}
		}
		if (keys[rightPress])
		{
			if (!collideRight) {
				Xchar += 0.004f;
			}
		}
		if (keys[upPress])
		{
			if (!collideUp) {
				Ychar += 0.004f;
			}
		}
		if (keys[downPress])
		{
			if (!collideDown) {
				Ychar -= 0.01f;
			}
		}
		stepCounter = stepCounter + 0.1f;
	}
	else {
		if (keys[leftPress])
		{
			if (!collideLeft) {
				Xchar -= movementSpeed;
			}
		}
		if (keys[rightPress])
		{
			if (!collideRight) {
				Xchar += movementSpeed;
			}
		}
		if (keys[upPress])
		{
			if (!collideUp) {
				Ychar += movementSpeed;
			}
		}
		if (keys[downPress])
		{
			if (!collideDown) {
				Ychar -= movementSpeed;
			}
		}
	}
}
