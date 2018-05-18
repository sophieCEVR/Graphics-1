#include "CornerPath.h"



CornerPath::CornerPath(char charIn, int xPosition, int yPosition, GLuint texture)
{
	objTexture = texture;
	charPassed = charIn;
	width = 1.05;
	height = 1.05;
	xObj = tileWidth * xPosition;
	yObj = tileHeight * yPosition;
}

void CornerPath::init() {

	//objTexture = loadPNG(objTexture);
	if (charPassed == '[') { //left path
		//objTexture = loadPNG("textures/path/l.png");
		pathOBB.vertOriginal[0].x = 0;
		pathOBB.vertOriginal[0].y = 0;

		pathOBB.vertOriginal[1].x = 0;
		pathOBB.vertOriginal[1].y = tileHeight;

		pathOBB.vertOriginal[2].x = tileWidth / 6;
		pathOBB.vertOriginal[2].y = tileHeight;

		pathOBB.vertOriginal[3].x = tileWidth / 6;
		pathOBB.vertOriginal[3].y = 0;
	}
	else if (charPassed == ']') { //right path
		//objTexture = loadPNG("textures/path/r.png");
		pathOBB.vertOriginal[0].x = tileWidth;
		pathOBB.vertOriginal[0].y = 0;

		pathOBB.vertOriginal[1].x = tileWidth;
		pathOBB.vertOriginal[1].y = tileHeight;

		pathOBB.vertOriginal[2].x = (tileWidth / 6) * 6;
		pathOBB.vertOriginal[2].y = tileHeight;

		pathOBB.vertOriginal[3].x = (tileWidth / 6) * 6;
		pathOBB.vertOriginal[3].y = 0;
	}
	else if (charPassed == '-') { //top path
		//objTexture = loadPNG("textures/path/t.png");
		pathOBB.vertOriginal[0].x = tileWidth;
		pathOBB.vertOriginal[0].y = tileHeight;

		pathOBB.vertOriginal[1].x = tileWidth;
		pathOBB.vertOriginal[1].y = (tileHeight / 6) * 6;

		pathOBB.vertOriginal[2].x = 0;
		pathOBB.vertOriginal[2].y = (tileHeight / 6) * 6;

		pathOBB.vertOriginal[3].x = 0;
		pathOBB.vertOriginal[3].y = tileHeight;
	}
	else if (charPassed == '~') { //bottom path
		//objTexture = loadPNG("textures/path/b.png");
		pathOBB.vertOriginal[0].x = tileWidth;
		pathOBB.vertOriginal[0].y = 0;

		pathOBB.vertOriginal[1].x = tileWidth;
		pathOBB.vertOriginal[1].y = tileHeight / 6;

		pathOBB.vertOriginal[2].x = 0;
		pathOBB.vertOriginal[2].y = tileHeight / 6;

		pathOBB.vertOriginal[3].x = 0;
		pathOBB.vertOriginal[3].y = 0;
	}
	else if (charPassed == '`') { //top left corner path
		//objTexture = loadPNG("textures/path/tlc.png"); 
		pathOBB.vertOriginal[0].x = 0;
		pathOBB.vertOriginal[0].y = tileHeight;

		pathOBB.vertOriginal[1].x = tileWidth / 2;
		pathOBB.vertOriginal[1].y = tileHeight;

		pathOBB.vertOriginal[2].x = tileWidth / 2;
		pathOBB.vertOriginal[2].y = (tileHeight / 2);// *2;

		pathOBB.vertOriginal[3].x = 0;
		pathOBB.vertOriginal[3].y = (tileHeight / 2);// *2;
	}
	else if (charPassed == '"') { //top right corner path
		//objTexture = loadPNG("textures/path/trc.png");
		pathOBB.vertOriginal[0].x = tileWidth;
		pathOBB.vertOriginal[0].y = tileHeight;

		pathOBB.vertOriginal[1].x = tileWidth;
		pathOBB.vertOriginal[1].y = (tileHeight / 2);// * 2;

		pathOBB.vertOriginal[2].x = (tileWidth / 2);// * 2;
		pathOBB.vertOriginal[2].y = (tileHeight / 2);// * 2;

		pathOBB.vertOriginal[3].x = (tileWidth / 2);// * 2;
		pathOBB.vertOriginal[3].y = tileHeight;
	}
	else if (charPassed == ',') { //bottom left corner
		//objTexture = loadPNG("textures/path/blc.png");
		pathOBB.vertOriginal[0].x = 0;
		pathOBB.vertOriginal[0].y = 0;

		pathOBB.vertOriginal[1].x = 0;
		pathOBB.vertOriginal[1].y = tileHeight /3;

		pathOBB.vertOriginal[2].x = tileWidth / 3;
		pathOBB.vertOriginal[2].y = tileHeight / 3;

		pathOBB.vertOriginal[3].x = tileWidth / 3;
		pathOBB.vertOriginal[3].y = 0;
	}
	else if (charPassed == '.') { //bottom right corner
		//objTexture = loadPNG("textures/path/brc.png");
		pathOBB.vertOriginal[0].x = tileWidth;
		pathOBB.vertOriginal[0].y = 0;

		pathOBB.vertOriginal[1].x = tileWidth;
		pathOBB.vertOriginal[1].y = tileHeight / 3;

		pathOBB.vertOriginal[2].x = (tileWidth / 3) * 2;
		pathOBB.vertOriginal[2].y = tileHeight / 3;

		pathOBB.vertOriginal[3].x = (tileWidth / 3) * 2;
		pathOBB.vertOriginal[3].y = 0;
	}
}

CornerPath::~CornerPath()
{
}

void CornerPath::additionalDisplay(){

	if (charPassed == '[') {
		glPushMatrix();
			glLineWidth(3.0);
			glTranslatef(xObj, yObj, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, objectMatrix);
		glPopMatrix();
	}
	else if (charPassed == ']') {
		glPushMatrix();
			glLineWidth(3.0);
			glTranslatef(xObj, yObj, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, objectMatrix);
		glPopMatrix();
	}
	else if(charPassed == '.' || charPassed == '~' || charPassed == ',') {
		glPushMatrix();		
			glLineWidth(3.0);
			glTranslatef(xObj, yObj, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, objectMatrix);
		glPopMatrix();
	}
	else {
		glPushMatrix();
			glLineWidth(3.0);
			glTranslatef(xObj, yObj, 0.0); 
			glGetFloatv(GL_MODELVIEW_MATRIX, objectMatrix);
		glPopMatrix();
	}

	pathOBB.transformPoints(objectMatrix);
}