#pragma once
#include <vector>
#include <windows.h>		// Header file for Windows
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations

class Node
{
public:
	Node(int xPosition, int YPosition);
	~Node();
	//void init();
	//void update();
	void display();
	void setStartNode();
	void setFinishNode();
	//GLuint loadPNG(char* name);


	//	bool bObstacle = false;			//Is the node an obstruction?
	bool isVisited = false;			//Have we searched this node before?
	bool isANeighbour = false;
	bool isStartNode = false;
	bool isFinishNode = false;
	int distanceToGoal;
	int distanceToStart;
	int totalFromBoth;
	int width = 40;
	int height = 40;
	int xPosition = 0;
	int yPosition = 0;
	int xPos = 0;
	int yPos = 0;
};