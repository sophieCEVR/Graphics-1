#pragma once

#include <windows.h>		// Header file for Windows
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations
class HUD
{
public:
	/***********************************************************************************************/
	/*											VARIABLES										   */
	/***********************************************************************************************/
	GLuint bone = 0;
	GLuint boneEmpty = 0;
	GLuint heart = 0;
	GLuint heartHalf = 0;
	GLuint heartEmpty = 0;
	GLuint chicken = 0;
	GLuint boostBar = 0;

	int health = 3;
	int boost = 0;

	int screenWidth = 0;
	int screenHeight = 0;
	float windowRepositionX = 0;
	float windowRepositionY = 0;

	int xPos = 10;/*
	int yPos = 0;*/

	int tileWidth = 40;
	int tileHeight = 40;
	int textureCount = 0;
	//std::string textureSource = "textures/";
	double width = 2;
	double height = 2;
	int xItem = 0;
	int yItem = 0;
	//bool debug = true;

	/***********************************************************************************************/
	/*											 METHODS										   */
	/***********************************************************************************************/
	HUD(int health, int boost, int screenWidth, int screenHeight);
	~HUD();
	void display();
	void init();
	void update(int health, int boost, float windowRepositionX, float windowRepositionY, int screenWidthIn, int screenHeightIn);
	GLuint loadPNG(char * name);
};

