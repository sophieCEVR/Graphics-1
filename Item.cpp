#include "Item.h"
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations

Item::Item() {}

Item::Item(int i, int y, GLuint texture){
	itemTexture = texture;
	width = 1;
	height = 1;
	xItem = tileWidth * i;
	yItem = tileHeight * y;

	init();
}

Item::~Item(){}

void Item::display() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, itemTexture);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	/********************************facing front or backwards**************************************/
	float itemMatrix[16];
	/********Position and Sizing ***********/
	glTranslatef(xItem, yItem, 0.0);

	//glScalef(2,2, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, itemMatrix);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(width, height);
		glTexCoord2f(0.0, 1.0); glVertex2f(width, tileHeight*height);
		glTexCoord2f(1.0, 1.0); glVertex2f(tileWidth*width, tileHeight*height);
		glTexCoord2f(1.0, 0.0); glVertex2f(tileWidth*width, height);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	//OBB Creation
	itemOBB.vertOriginal[0].x = -width;
	itemOBB.vertOriginal[0].y = -height;

	itemOBB.vertOriginal[1].x = -width;
	itemOBB.vertOriginal[1].y = tileHeight * height;

	itemOBB.vertOriginal[2].x = tileWidth * width;
	itemOBB.vertOriginal[2].y = tileHeight * height;

	itemOBB.vertOriginal[3].x = tileWidth * width;
	itemOBB.vertOriginal[3].y = -height;


	itemOBB.transformPoints(itemMatrix);
}

void Item::init() {}