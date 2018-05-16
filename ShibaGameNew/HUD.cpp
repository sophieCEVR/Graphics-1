#include "HUD.h"

GLuint HUD::loadPNG(char* name)
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}


HUD::HUD(int health, int boost, int screenWidthIn, int screenHeightIn) {
	screenWidth -= screenWidthIn;// / 2 - 10;
	screenHeight = screenHeightIn;// / 2 - 50;
}


HUD::~HUD(){}


void HUD::display() {
	/**********************************************************************/
								//firstHeart
	/**********************************************************************/

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	if (health >= 2) {
		glBindTexture(GL_TEXTURE_2D, heart);
	}
	else if (health == 1) {
		glBindTexture(GL_TEXTURE_2D, heartHalf);
	}
	else if (health == 0) {
		glBindTexture(GL_TEXTURE_2D, heartEmpty);
	}

	/********Position and Sizing ***********/
	if (screenWidth > 1600) {
		glTranslatef(((-screenWidth / 2)+125) + windowRepositionX, ((screenHeight / 2)-10) + windowRepositionY, 0.0);
	}
	else {
		glTranslatef(((-screenWidth / 2)+100) + windowRepositionX, (screenHeight / 2-50) + windowRepositionY, 0.0);
	}
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
		glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
		glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
		glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	/**********************************************************************/
								//secondHeart
	/**********************************************************************/

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	if (health >= 4) {
		glBindTexture(GL_TEXTURE_2D, heart);
	}
	else if (health == 3) {
		glBindTexture(GL_TEXTURE_2D, heartHalf);
	}
	else if (health <= 2) {
		glBindTexture(GL_TEXTURE_2D, heartEmpty);
	}

	/********Position and Sizing ***********/
	if (screenWidth > 1600) {
		glTranslatef(((-screenWidth / 2) + 205) + windowRepositionX, ((screenHeight / 2) - 10) + windowRepositionY, 0.0);
	}
	else {
		glTranslatef(((-screenWidth / 2) + 180) + windowRepositionX, (screenHeight / 2 - 50) + windowRepositionY, 0.0);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
	glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
	glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
	glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	/**********************************************************************/
								//thirdHeart
	/**********************************************************************/

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	if (health == 6) {
		glBindTexture(GL_TEXTURE_2D, heart);
	}
	else if (health == 5) {
		glBindTexture(GL_TEXTURE_2D, heartHalf);
	}
	else if (health < 5) {
		glBindTexture(GL_TEXTURE_2D, heartEmpty);
	}

	/********Position and Sizing ***********/
	if (screenWidth > 1600) {
		glTranslatef(((-screenWidth / 2) + 285) + windowRepositionX, ((screenHeight / 2) - 10) + windowRepositionY, 0.0);
	}
	else {
		glTranslatef(((-screenWidth / 2) + 260) + windowRepositionX, (screenHeight / 2 - 50) + windowRepositionY, 0.0);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
	glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
	glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
	glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	/**********************************************************************/
								//firstBone
	/**********************************************************************/

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	if (boost >= 1) {
		glBindTexture(GL_TEXTURE_2D, bone);
	}
	else if (boost == 0) {
		glBindTexture(GL_TEXTURE_2D, boneEmpty);
	}

	/********Position and Sizing ***********/
	if (screenWidth > 1600) {
		glTranslatef(((screenWidth / 2)-205) + windowRepositionX, ((screenHeight / 2)-10) + windowRepositionY, 0.0);
	}
	else {
		glTranslatef(((screenWidth / 2) - 185) + windowRepositionX, (screenHeight / 2 - 50) + windowRepositionY, 0.0);
	}
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
		glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
		glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
		glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	/**********************************************************************/
								//secondBone
	/**********************************************************************/

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	if (boost >= 2) {
		glBindTexture(GL_TEXTURE_2D, bone);
	}
	else if (boost < 2) {
		glBindTexture(GL_TEXTURE_2D, boneEmpty);
	}

	/********Position and Sizing ***********/
	if (screenWidth > 1600) {
		glTranslatef(((screenWidth / 2) - 285) + windowRepositionX, ((screenHeight / 2) - 10) + windowRepositionY, 0.0);
	}
	else {
		glTranslatef(((screenWidth / 2) - 260) + windowRepositionX, (screenHeight / 2 - 50) + windowRepositionY, 0.0);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
	glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
	glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
	glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	/**********************************************************************/
								//thirdBone
	/**********************************************************************/

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	if (boost == 3) {
		glBindTexture(GL_TEXTURE_2D, bone);
	}
	else if (boost < 3) {
		glBindTexture(GL_TEXTURE_2D, boneEmpty);
	}

	/********Position and Sizing ***********/
	if (screenWidth > 1600) {
		glTranslatef(((screenWidth / 2) - 365) + windowRepositionX, ((screenHeight / 2) - 10) + windowRepositionY, 0.0);
	}
	else {
		glTranslatef(((screenWidth / 2) - 335) + windowRepositionX, (screenHeight / 2 - 50) + windowRepositionY, 0.0);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
	glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
	glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
	glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	if (boost == 3) {
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, boostBar);

		/********Position and Sizing ***********/
		if (screenWidth > 1600) {
			glTranslatef( windowRepositionX-400, ((-screenHeight / 3)+35) + windowRepositionY, 0.0);
		}
		else {
			glTranslatef( windowRepositionX-400, (-screenHeight / 3 ) + windowRepositionY, 0.0);
		}
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
			glTexCoord2f(0.0, 1.0); glVertex2f(0, 80);
			glTexCoord2f(1.0, 1.0); glVertex2f(800, 80);
			glTexCoord2f(1.0, 0.0); glVertex2f(800, 0);
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}
}

void HUD::update(int healthIn, int boostIn, float windowRepositionXIn, float windowRepositionYIn, int screenWidthIn, int screenHeightIn) {
	health = healthIn;
	boost = boostIn;
	screenHeight = screenHeightIn;
	screenWidth = screenWidthIn;
	windowRepositionX = windowRepositionXIn;
	windowRepositionY = windowRepositionYIn;
	HUD::display();
}

void HUD::init() {
	bone = loadPNG("textures/Items/bone.png");
	boneEmpty = loadPNG("textures/Items/boneEmpty.png");
	heart = loadPNG("textures/Items/heart.png");
	heartHalf = loadPNG("textures/Items/heartHalf.png");
	heartEmpty = loadPNG("textures/Items/heartEmpty.png");
	chicken = loadPNG("textures/Items/chicken.png");
	boostBar = loadPNG("textures/Items/boostBar.png");
}
