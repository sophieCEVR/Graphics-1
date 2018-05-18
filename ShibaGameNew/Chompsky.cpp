#include "Chompsky.h"



Chompsky::Chompsky()
{
	texturesNormal = false;
	Xchar = 100;							//starting x position for specified character
	Ychar = 650;							//starting y position for specified character
	Xfb1 = 12.5;							//X axis int #1 when facing forward/backwards
	Xfb2 = 12.5;							//X axis int #2 when facing forward/backwards
	Yfb1 = 20.5;							//y axis int #1 when facing forward/backwards
	Yfb2 = 12.5;							//y axis int #2 when facing forward/backwards
	Xlr1 = 15;								//X axis int #1 when facing left/right
	Xlr2 = 17.5;							//X axis int #2 when facing left/right
	Ylr1 = 15;								//y axis int #1 when facing left/right
	Ylr2 = 15;								//y axis int #2 when facing left/right
	textureFolder = "Pug";
	movementSpeed = 6.2;
}

Chompsky::~Chompsky()
{
}

void Chompsky::additionalDisplay()
{
	glLoadIdentity();

	/**********************************************************************************************/
	//Chompsky Character Creation
	/**********************************************************************************************/

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	if (!chompskyActive) {
		if (chompskySitCounter > 150.00) {
			chompskySitCounter = 0.00;
		}
		if (distance > 125) {
			if (chompskySitCounter < 25) {
				glBindTexture(GL_TEXTURE_2D, pugs1);
			}
			else if (chompskySitCounter > 25 && chompskySitCounter < 50) {
				glBindTexture(GL_TEXTURE_2D, pugs2);
			}
			else if (chompskySitCounter > 50 && chompskySitCounter < 75) {
				glBindTexture(GL_TEXTURE_2D, pugs3);
			}
			else if (chompskySitCounter > 75 && chompskySitCounter < 100) {
				glBindTexture(GL_TEXTURE_2D, pugs4);
			}
			else if (chompskySitCounter > 100 && chompskySitCounter < 125) {
				glBindTexture(GL_TEXTURE_2D, pugs5);
			}
			else if (chompskySitCounter > 125 && chompskySitCounter < 150) {
				glBindTexture(GL_TEXTURE_2D, pugs6);
			}
		}
	}
	glPopMatrix();

	/********************************Chompsky facing front or backwards**************************************/

	if (!chompskyActive) {
		glPushMatrix();
		/********Position and Sizing ***********/
		glTranslatef(Xchar, Ychar, 0.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex2f(-12.5, -17.5);
			glTexCoord2f(0.0, 1.0); glVertex2f(-12.5, 12.5);
			glTexCoord2f(1.0, 1.0); glVertex2f(12.5, 12.5);
			glTexCoord2f(1.0, 0.0); glVertex2f(12.5, -17.5);
	
		glEnd();

		/********Texture Ending ***********/
		glPopMatrix();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	/********************************Chompsky distance calculator**************************************/
	//glPushMatrix();
	//glLineWidth(3.0);
	//if (distance < 150) {
	//	glColor3f(1.0, 1.0, 0.0);
	//}
	//glBegin(GL_LINES);
	//	glVertex2f(Xchar, Ychar);
	//	glVertex2f(Xobject, Yobject);
	//glEnd();
	//glPopMatrix();

	//std::cout << distance << std::endl;
	//std::cout << Xchar << std::endl;
	//std::cout << Xobject << std::endl;
	/*if ((Ychar == (Yobject - 100))) {
		std::cout << "ACTIVE" << std::endl;
	}

	if (chompskyInPlace) {
		std::cout << "IN PLACE" << std::endl;
	}*/
	/**********************************************************************************************/
	//OBB Creation
	/**********************************************************************************************/

	//shibaOBB.transformPoints(shibaMatrix);
	//pugOBB.transformPoints(pugMatrix);

	//if (pugOBB.SAT2D(shibaOBB))
	//	glColor3f(1.0, 0.0, 1.0);
	//else
	//	glColor3f(0.0, 0.0, 1.0);
	//pugOBB.drawOBB();

	//shibaOBB.drawOBB();
	if (chompskyActive) {
		texturesNormal = true;
	}
}

//updates variables based on user interaction
void Chompsky::additionalUpdate() {
	std::cout << "Chompsky in place ? " << chompskyInPlace << "Chompsky Y val ? " << Ychar << "Hanzo Y val ? " << Yobject << "Chompsky X val ? " << Xchar << "Hanzo X val ? " << Xobject << std::endl;
	if (distance < 150 && chompskyActive == false) {
		chompskyActive = true;
	}
	if (!chompskyInPlace && (((Ychar >(Yobject - 30) && (Ychar < (Yobject - 20)) && ((Xchar < (Xobject -10)) && (Xchar >(Xobject - 25))))))) {
		chompskyInPlace = true;
	}

	chompskySitCounter = chompskySitCounter + 0.09f;
}


void Chompsky::additionalInit()
{
	// pug sitting
	pugs1 = loadPNG("textures/Pug/s1.png");
	pugs2 = loadPNG("textures/Pug/s2.png");
	pugs3 = loadPNG("textures/Pug/s3.png");
	pugs4 = loadPNG("textures/Pug/s4.png");
	pugs5 = loadPNG("textures/Pug/s5.png");
	pugs6 = loadPNG("textures/Pug/s6.png");
}

void Chompsky::additionalProcessKeys(bool keys[256]) {

	if ((chompskyActive && !chompskyInPlace)) {
		if (Xchar < (Xobject-20)) {
			Xchar += movementSpeed; 
		}
		else if (Xchar > (Xobject-10)) {
			Xchar -= movementSpeed; 
		}
		if (Ychar > (Yobject - 30)) {
			Ychar -= movementSpeed; 
		}
		else if (Ychar < (Yobject - 20)) {
			Ychar += movementSpeed; 
		}
	}
	else if (chompskyActive && chompskyInPlace) {
			if (boostMeter == 3) {
				if (keys[VK_SPACE]) {
					spacePressed = true;
				}
			}
			if (spacePressed && !collisionBoost) {
				movementSpeed = 10;
				characterMovementSpeed = 4.00f;
			}
			else if (spacePressed && collisionBoost) {
				movementSpeed = 0;
			}
			else {
				movementSpeed = 6;
			}
			
			if (keys[leftPress])
			{
				if (!collideLeft) {
				//	Xchar = Xchar - 10;
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
