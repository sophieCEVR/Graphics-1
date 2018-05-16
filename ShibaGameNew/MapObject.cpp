#include "MapObject.h"
//#include <chrono>
//#include <thread>
//
//using namespace std::this_thread; // sleep_for, sleep_until
//using namespace std::chrono; // nanoseconds, system_clock, seconds

//GLuint MapObject::loadPNG(char* name)
//{
//	// Texture loading object
//	nv::Image img;
//
//	GLuint myTextureID;
//
//	// Return true on success
//	if (img.loadImageFromFile(name))
//	{
//		glGenTextures(1, &myTextureID);
//		glBindTexture(GL_TEXTURE_2D, myTextureID);
//		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
//	}
//
//	else
//		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);
//
//	return myTextureID;
//}

MapObject::MapObject(int xPosition, int yPosition, GLuint texture)
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	objTexture = texture;
	xObj = tileWidth * xPosition;
	yObj = tileHeight * yPosition;
	init();
}

MapObject::MapObject() {}
MapObject::~MapObject() {}

void MapObject::display() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, objTexture);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	/********************************facing front or backwards**************************************/
	float objectMatrix[16];
	/********Position and Sizing ***********/
	glTranslatef(xObj, yObj, 0.0);

	//glScalef(2,2, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, objectMatrix);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
		glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
		glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
		glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();



	/********Texture Ending ***********/
	glPopMatrix();
	//	glDisable(GL_TEXTURE_2D);
	additionalDisplay();

}

void MapObject::init() {
	//sleep_for(nanoseconds(10));
	/*
	srand((time(NULL)*yObj)*(time(NULL)*xObj));
	textureSource = textureSource + to_string((rand()*(rand())) % textureCount + 1) + ".png";*/
	//char char_array[23];
	//strcpy(char_array, textureSource.c_str());
	//objTexture = loadPNG(char_array);
	//objTexture = textureSource;
}

void MapObject::additionalDisplay() {}
