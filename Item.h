#pragma once
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations
class Item
{
public:
	/***********************************************************************************************/
	/*											VARIABLES										   */
	/***********************************************************************************************/
	int xPosition = 0;
	int yPosition = 0;
	//int randomizeMapObject = 0;

	int tileWidth = 40;
	int tileHeight = 40;
	//std::string textureSource = "textures/";
	double width = 1;
	double height = 1;
	int xItem = 0;
	int yItem = 0;
	GLuint itemTexture = 0;
	//bool debug = true;

	//OBB declaration
	OBB itemOBB;							//allows for use of oriented bounding box collision detection 

	/***********************************************************************************************/
	/*											 METHODS										   */
	/***********************************************************************************************/
	Item();
	Item(int i, int y, GLuint texture);
	~Item();
	void display();
	//GLuint loadPNG(char* name); 
	virtual void init();
	//virtual void additionalDisplay();
	//void processKeys(bool keys[256];
};

