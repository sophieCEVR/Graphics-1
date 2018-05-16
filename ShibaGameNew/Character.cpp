#include "Character.h"

GLuint Character::loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}

Character::Character() {}							//base class not instantiated
Character::~Character() {}							//base class not instantiated

void Character::display() {
		if(texturesNormal){
			glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_TEXTURE_2D);

			if (stepCounter <= 10) {
				if (forward) {
					glBindTexture(GL_TEXTURE_2D, f1);
				}
				else if (backward) {
					glBindTexture(GL_TEXTURE_2D, b1);
				}
				else if (left) {
					glBindTexture(GL_TEXTURE_2D, l1);
				}
				else if (right) {
					glBindTexture(GL_TEXTURE_2D, r1);
				}
			}
			else if (stepCounter > 10 && stepCounter <= 20) {
				if (forward) {
					glBindTexture(GL_TEXTURE_2D, f2);
				}
				else if (backward) {
					glBindTexture(GL_TEXTURE_2D, b2);
				}
				else if (left) {
					glBindTexture(GL_TEXTURE_2D, l2);
				}
				else if (right) {
					glBindTexture(GL_TEXTURE_2D, r2);
				}
			}
			else if (stepCounter > 20 && stepCounter <= 30) {
				if (forward) {
					glBindTexture(GL_TEXTURE_2D, f3);
				}
				else if (backward) {
					glBindTexture(GL_TEXTURE_2D, b3);
				}
				else if (left) {
					glBindTexture(GL_TEXTURE_2D, l3);
				}
				else if (right) {
					glBindTexture(GL_TEXTURE_2D, r3);
				}
			}
			else if (stepCounter > 30) {
				if (forward) {
					glBindTexture(GL_TEXTURE_2D, f4);
				}
				else if (backward) {
					glBindTexture(GL_TEXTURE_2D, b4);
				}
				else if (left) {
					glBindTexture(GL_TEXTURE_2D, l4);
				}
				else if (right) {
					glBindTexture(GL_TEXTURE_2D, r4);
				}
			}
			if (stepCounter > 39.00) {
				stepCounter = 0.00;
			}
			/********************************facing front or backwards**************************************/
			/********Position and Sizing ***********/
			glTranslatef(Xchar, Ychar, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, charMatrix);
			glBegin(GL_QUADS);
				if (forward || backward) {
					glTexCoord2f(0.0, 0.0); glVertex2f(-Xfb1, -Yfb1);
					glTexCoord2f(0.0, 1.0); glVertex2f(-Xfb2, Yfb2);
					glTexCoord2f(1.0, 1.0); glVertex2f(Xfb2, Yfb2);
					glTexCoord2f(1.0, 0.0); glVertex2f(Xfb1, -Yfb1);
				}
				else {
					glTexCoord2f(0.0, 0.0); glVertex2f(-Xlr1, -Ylr1);
					glTexCoord2f(0.0, 1.0); glVertex2f(-Xlr1, Ylr2);
					glTexCoord2f(1.0, 1.0); glVertex2f(Xlr2, Ylr2);
					glTexCoord2f(1.0, 0.0); glVertex2f(Xlr2, -Ylr1);
				}
			glEnd();

			/********Texture Ending ***********/
			glPopMatrix();

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}

	additionalDisplay();

	charOBB.transformPoints(charMatrix);
}

void Character::additionalDisplay(){}


//updates variables based on user interaction
void Character::update(bool keys[256]) {
	distance = sqrt(((Xchar - Xobject)*(Xchar - Xobject)) + ((Ychar - Yobject)*(Ychar - Yobject)));
	additionalUpdate();
}
void Character::additionalUpdate()
{}

void Character::init(){
	
	/********************************shiba png loading**************************************/

	// walking forward

	char char_arrayf1[23];
	texture = textureSource + textureFolder + "/f1.png";
	strcpy(char_arrayf1, texture.c_str());
	f1 = loadPNG(char_arrayf1);

	char char_arrayf2[23];
	texture = textureSource + textureFolder + "/f2.png";
	strcpy(char_arrayf2, texture.c_str());
	f2 = loadPNG(char_arrayf2);

	char char_arrayf3[23];
	texture = textureSource + textureFolder + "/f3.png";
	strcpy(char_arrayf3, texture.c_str());
	f3 = loadPNG(char_arrayf3);

	char char_arrayf4[23];
	texture = textureSource + textureFolder + "/f4.png";
	strcpy(char_arrayf4, texture.c_str());
	f4 = loadPNG(char_arrayf4);

	// walking backwards

	char char_arrayb1[23];
	texture = textureSource + textureFolder + "/b1.png";
	strcpy(char_arrayb1, texture.c_str());
	b1 = loadPNG(char_arrayb1);

	char char_arrayb2[23];
	texture = textureSource + textureFolder + "/b2.png";
	strcpy(char_arrayb2, texture.c_str());
	b2 = loadPNG(char_arrayb2);

	char char_arrayb3[23];
	texture = textureSource + textureFolder + "/b3.png";
	strcpy(char_arrayb3, texture.c_str());
	b3 = loadPNG(char_arrayb3);

	char char_arrayb4[23];
	texture = textureSource + textureFolder + "/b4.png";
	strcpy(char_arrayb4, texture.c_str());
	b4 = loadPNG(char_arrayb4);

	// walking left

	char char_arrayl1[23];
	texture = textureSource + textureFolder + "/l1.png";
	strcpy(char_arrayl1, texture.c_str());
	l1 = loadPNG(char_arrayl1);

	char char_arrayl2[23];
	texture = textureSource + textureFolder + "/l2.png";
	strcpy(char_arrayl2, texture.c_str());
	l2 = loadPNG(char_arrayl2);

	char char_arrayl3[23];
	texture = textureSource + textureFolder + "/l3.png";
	strcpy(char_arrayl3, texture.c_str());
	l3 = loadPNG(char_arrayl3);

	char char_arrayl4[23];
	texture = textureSource + textureFolder + "/l4.png";
	strcpy(char_arrayl4, texture.c_str());
	l4 = loadPNG(char_arrayl4);

	// walking right

	char char_arrayr1[23];
	texture = textureSource + textureFolder + "/r1.png";
	strcpy(char_arrayr1, texture.c_str());
	r1 = loadPNG(char_arrayr1);

	char char_arrayr2[23];
	texture = textureSource + textureFolder + "/r2.png";
	strcpy(char_arrayr2, texture.c_str());
	r2 = loadPNG(char_arrayr2);

	char char_arrayr3[23];
	texture = textureSource + textureFolder + "/r3.png";
	strcpy(char_arrayr3, texture.c_str());
	r3 = loadPNG(char_arrayr3);

	char char_arrayr4[23];
	texture = textureSource + textureFolder + "/r4.png";
	strcpy(char_arrayr4, texture.c_str());
	r4 = loadPNG(char_arrayr4);

	/**********************************************************************************************/
	//OBB init
	/**********************************************************************************************/

	//charOBB.vertOriginal[0].x = -Xfb1;
	//charOBB.vertOriginal[0].y = -Yfb1;

	//charOBB.vertOriginal[1].x = -Xfb2;
	//charOBB.vertOriginal[1].y = Yfb2;

	//charOBB.vertOriginal[2].x = Xfb2;
	//charOBB.vertOriginal[2].y = Yfb2;

	//charOBB.vertOriginal[3].x = Xfb1;
	//charOBB.vertOriginal[3].y = -Yfb1;

	additionalInit();
}

void Character::additionalInit() {}

void Character::processKeys(bool keys[256], int boostMeterIn) {
	boostMeter = boostMeterIn;
//	std::cout << boostMeter << std::endl;
	if (keys[leftPress] || keys[rightPress] || keys[upPress] || keys[downPress])
	{
		stepCounter = stepCounter + characterMovementSpeed;
	}
	if (keys[leftPress])
	{
		forward = false;
		backward = false;
		left = true;
		right = false;
	}
	else if (keys[rightPress]) {
		forward = false;
		backward = false;
		left = false;
		right = true;
	}
	else if (keys[upPress]) {
		forward = true;
		backward = false;
		left = false;
		right = false;
	}
	else if (keys[downPress]) {
		forward = false;
		backward = true;
		left = false;
		right = false;
	}
	additionalProcessKeys(keys);
}

void Character::additionalProcessKeys(bool keys[256]) {}
