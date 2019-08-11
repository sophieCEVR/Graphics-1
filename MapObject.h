#pragma once
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations
#include <windows.h>		// Header file for Windows
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class MapObject
{
public:
	/***********************************************************************************************/
	/*											VARIABLES										   */
	/***********************************************************************************************/
	int xPosition = 0;
	int yPosition = 0;
	int randomizeMapObject = 0;

	int tileWidth = 40;
	int tileHeight = 40;
	int textureCount = 0; 
	//std::string textureSource = "textures/";
	double width = 1;
	double height = 1;
	int xObj = 0;
	int yObj = 0; 
	GLuint objTexture = 0;
	bool debug = true; 

	/***********************************************************************************************/
	/*											 METHODS										   */
	/***********************************************************************************************/
	void display();
	MapObject();
	MapObject(int xPosition, int yPosition, GLuint texture);
	~MapObject(); 
	//GLuint loadPNG(char* name); 
	virtual void init();
	virtual void additionalDisplay();
	//void processKeys(bool keys[256];
};

