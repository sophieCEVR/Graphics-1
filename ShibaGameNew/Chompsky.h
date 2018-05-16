#ifndef CHOMPSKY_H
#define CHOMPSKY_H

#include "Character.h"

class Chompsky :
	public Character
{
public:

	/***********************************************************************************************/
	/*											VARIABLES										   */
	/***********************************************************************************************/
	bool chompskyActive = false;
	bool chompskyInPlace = false;
	float chompskySitCounter = 0.00;
	float characterMovementSpeed = 1.2f;
	//float values for vertex creation based on characters current direction 


	GLuint pugs1 = 0;
	GLuint pugs2 = 0;
	GLuint pugs3 = 0;
	GLuint pugs4 = 0;
	GLuint pugs5 = 0;
	GLuint pugs6 = 0;

	/***********************************************************************************************/
	/*											 METHODS										   */
	/***********************************************************************************************/

	Chompsky();
	~Chompsky();
	//void init();
	void additionalProcessKeys(bool keys[256]);
	void additionalDisplay();
	void additionalUpdate();
	void additionalInit();


};

#endif
