#include "MiniGameBarn.h"



MiniGameBarn::MiniGameBarn(int xPosition, int yPosition, GLuint texture) : MapObject(xPosition, yPosition, texture) {}


MiniGameBarn::~MiniGameBarn(){}

void MiniGameBarn::importOpenTexture(GLuint textureOpen){
	this->textureOpen = textureOpen;
}

void MiniGameBarn::init() {
	width = 8;
	height = 8;
	mgOBB.vertOriginal[0].x = 0;
	mgOBB.vertOriginal[0].y = 0;

	mgOBB.vertOriginal[1].x = 0;
	mgOBB.vertOriginal[1].y = tileHeight*height;

	mgOBB.vertOriginal[2].x = (tileWidth*width);
	mgOBB.vertOriginal[2].y = tileHeight*height;

	mgOBB.vertOriginal[3].x = tileWidth*width;
	mgOBB.vertOriginal[3].y = 0;
}


void MiniGameBarn::additionalDisplay() {
	glPushMatrix();
		glLineWidth(3.0);
		glTranslatef(xObj, yObj, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, objectMatrix);
	glPopMatrix();
	mgOBB.transformPoints(objectMatrix);
}