#ifndef CHARACTER_H
#define CHARACTER_H

#include <windows.h>		// Header file for Windows
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations

#include <iostream>
#include <string>
#include <cstdlib>

class Character
{
public:
	/***********************************************************************************************/
	/*											VARIABLES										   */
	/***********************************************************************************************/


	int leftPress = VK_LEFT;
	int rightPress = VK_RIGHT;
	int upPress = VK_UP;
	int downPress = VK_DOWN; 
	int distance = 0;						//gives distance between two points.
	int boostMeter = 0;

	//Timing related variables
	__int64 prevTime = 0;				// Previous count
	double timerFrequencyRecip = 0.0000005;
	//double deltaT = 0;
	float timer = 0;

	float charMatrix[16];
	float characterMovementSpeed = 0.8f;	//movement speed for specified character, differs how quickly the character animation works, how quickly the character moves its legs
	float Xchar;							//starting x position for specified character
	float Ychar;							//starting y position for specified character
	float Xobject;							//starting x position for specified object/point (for distance calculations)
	float Yobject;							//starting y position for specified object/point (for distance calculations)

	float stepCounter = 0;					//counts the "steps" to tell the character when to change texture
	float movementSpeed = 2;				//Preset movement speed of all active sprites

	//directional bools for sprite animations
	bool texturesNormal = true;				//used for inactive characters to stop texture overlapping
	bool forward = true;					//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.
	bool backward = false;					//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.
	bool left = false;						//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.
	bool right = false;						//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.
	bool collideLeft = false;
	bool collideRight = false;
	bool collideUp = false;
	bool collideDown = false;
	bool spacePressed = false;
	bool collisionBoost = false;
	bool stunned = false;

	//float values for vertex creation based on characters current direction 
	float Xfb1 = 0;							//X axis int #1 when facing forward/backwards
	float Xfb2 = 0;							//X axis int #2 when facing forward/backwards
	float Yfb1 = 0;							//y axis int #1 when facing forward/backwards
	float Yfb2 = 0;							//y axis int #2 when facing forward/backwards
	float Xlr1 = 0;							//X axis int #1 when facing left/right
	float Xlr2 = 0;							//X axis int #2 when facing left/right
	float Ylr1 = 0;							//y axis int #1 when facing left/right
	float Ylr2 = 0;							//y axis int #2 when facing left/right

	//texture handling variables
	GLuint f1 = 0;							//GLuint identifying texture 1 of 4 to be used when facing forward.
	GLuint f2 = 0;							//GLuint identifying texture 2 of 4 to be used when facing forward.
	GLuint f3 = 0;							//GLuint identifying texture 3 of 4 to be used when facing forward.
	GLuint f4 = 0;							//GLuint identifying texture 4 of 4 to be used when facing forward.
	GLuint b1 = 0;							//GLuint identifying texture 1 of 4 to be used when facing backward.
	GLuint b2 = 0;							//GLuint identifying texture 2 of 4 to be used when facing backward.
	GLuint b3 = 0;							//GLuint identifying texture 3 of 4 to be used when facing backward.
	GLuint b4 = 0;							//GLuint identifying texture 4 of 4 to be used when facing backward.
	GLuint l1 = 0;							//GLuint identifying texture 1 of 4 to be used when facing left.
	GLuint l2 = 0;							//GLuint identifying texture 2 of 4 to be used when facing left.
	GLuint l3 = 0;							//GLuint identifying texture 3 of 4 to be used when facing left.
	GLuint l4 = 0;							//GLuint identifying texture 4 of 4 to be used when facing left.
	GLuint r1 = 0;							//GLuint identifying texture 1 of 4 to be used when facing right.
	GLuint r2 = 0;							//GLuint identifying texture 2 of 4 to be used when facing right.
	GLuint r3 = 0;							//GLuint identifying texture 3 of 4 to be used when facing right.
	GLuint r4 = 0;							//GLuint identifying texture 4 of 4 to be used when facing right.
	GLuint v1 = 0;							//GLuint identifying texture 1 of 2 to be used when stunned.
	GLuint v2 = 0;							//GLuint identifying texture 2 of 2 to be used when stunned.

	//OBB declaration
	OBB charOBB;							//allows for use of oriented bounding box collision detection 

	std::string textureFolder = "";
	std::string textureSource = "textures/";
	std::string texture = "";
	/***********************************************************************************************/
	/*											 METHODS										   */
	/***********************************************************************************************/


	void display();					//basic movement instructions for all characters in their default states
	virtual void additionalDisplay();
	void update(bool keys[256]);							//updates
	virtual void additionalUpdate();
	virtual void additionalInit();
											//virtual int characterState();			//identifies which state the character is in via an int and returns this to the state machine in the main class. Preset to 0 on main character class
											//virtual void characterMove();			//has instructions on how the character should move in specified states
	void processKeys(bool keys[256], int boostMeterIn);		//allows for processing of key presses
	virtual void additionalProcessKeys(bool keys[256]);
	GLuint loadPNG(char* name);			//allows for texture loading 
	virtual void init();							//

	Character();							//base class not instantiated
	~Character();							//base class not instantiated
};
#endif

