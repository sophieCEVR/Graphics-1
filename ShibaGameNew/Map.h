#ifndef MAP_H
#define MAP_H

#include <windows.h>		// Header file for Windows
#include <iostream>
#include <fstream>
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations
#include "House.h"
#include "Bush.h"
#include "Path.h"
#include "CornerPath.h"
#include "Item.h"
#include "Bone.h"
#include "Heart.h"
#include "Chicken.h"
#include "Node.h"
#include "MiniGameBarn.h"
#include <list>

//#include "Main.cpp"

class Map
{
public:

	/***********************************************************************************************/
	/*											VARIABLES										   */
	/***********************************************************************************************/
	GLuint background = 0;
	GLuint house = 0;
	GLuint bush = 0;
	GLuint path = 0;
	GLuint bone = 0;
	GLuint heart = 0;
	GLuint chicken = 0;
	GLuint miniGameBarnOpen = 0;
	GLuint miniGameBarnClosed = 0;

	int randomize = 0;
	int charsInFile = 137;

	bool twoPlayerGame = false;

	/***********************************************************************************************/
	/*											 METHODS										   */
	/***********************************************************************************************/

	Map();
	~Map();
	GLuint loadPNG(char * name);
	GLuint loadPNGMap(char * name);
	list<MapObject*> objectList;
	list<Item*> itemList;
	Chicken* chickenPointer;
	vector<GLuint> housesVector;
	vector<GLuint> pathVector;
	vector<GLuint> cornerPathVector;
	vector<GLuint> bushVector;
	vector<Node*> nodeVector;
	void display();
	void init();
	void mapGenerator();

};
#endif
