#include "Node.h"

//GLuint Node::loadPNG(char* name)
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
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

Node::Node(int xPosition, int yPosition)
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	xPos = width*xPosition;
	yPos = height*yPosition;

}


Node::~Node()
{
}

void Node::display() {

	glPushMatrix();
	glTranslatef(xPos, yPos, 0.0);
	glBegin(GL_LINE_LOOP);
		 glVertex2f(0, 0);
		 glVertex2f(0, height);
		 glVertex2f(width, height);
		 glVertex2f(width, 0);
	glEnd();
	glPopMatrix();

}
//	nodes - new sNode[nMapWidth * nMapHeight];
//	for (int x = 0; x < nMapWidth; x++) {
//		for (int y = 0; y < nMapHeight; y++) {
//			nodes[y * nMapWidth + x].x = x;
//			nodes[y * nMapWidth + x].y = y;
//			nodes[y * nMapWidth + x].bObstacle = false;
//			nodes[y * nMapWidth + x].parent = nullptr;
//			nodes[y * nMapWidth + x].bVisited = false;
//		}
//	}
//}
//
//void Node::update() {
//	int nNodeSize = 0;
//	int nNodeBorder = 2;
//
//	Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
//
//	int x = 0; 
//}

void Node::setStartNode() {
	isStartNode = true;
}

void Node::setFinishNode() {
	isFinishNode = true;
}