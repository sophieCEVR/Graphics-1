#pragma once
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations
#include <windows.h>		// Header file for Windows
#include <iostream>
#include <Mmsystem.h>

class Menu
{
public:
	int menuCard = 1;
	int outcomeCard = 0;
	//texture handling variables
	GLuint menu1 = 0;							//GLuint identifying texture 1 of 4 to be used when facing forward.
	GLuint menu2 = 0;							//GLuint identifying texture 2 of 4 to be used when facing forward.
	GLuint howToPlay = 0;							//GLuint identifying texture 2 of 4 to be used when facing forward.
	GLuint winSingle = 0;							//GLuint identifying texture 2 of 4 to be used when facing forward.
	GLuint lossHealth = 0;							//GLuint identifying texture 2 of 4 to be used when facing forward.
	
	bool singlePlayerActivated = false;
	bool twoPlayerActivated = false;
	bool quit = false;
	int screenWidth;
	int screenHeight;
	
	Menu();
	~Menu();
	void init(int screenHeight, int screenWidth);
	void update(int mouseX, int mouseY, bool leftClick);
	void display(int screenHeight, int screenWidth);
};

