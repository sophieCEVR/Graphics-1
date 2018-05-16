#ifndef HANZO_H
#define HANZO_H

#include "Character.h"

class Hanzo :
	public Character
{
public:

	/***********************************************************************************************/
	/*											VARIABLES										   */
	/***********************************************************************************************/

	//Lead related Variables
	bool lead = false;
	//float timerCurrent = 0f;
	//float timerTotal = 5f;
//	std::string texturePath = "Shiba";

	/***********************************************************************************************/
	/*											 METHODS										   */
	/***********************************************************************************************/

	Hanzo();							//constructor
	void additionalDisplay();
	~Hanzo();							//deconstructor
	//void init();						//load on initialising method
	void additionalProcessKeys(bool keys[256]);					//key presses specific to hanzo character
};

#endif
