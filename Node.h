#pragma once
#include <vector>
#include <windows.h>		// Header file for Windows
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations

class Node
{
public:
	Node(int xPosition, int YPosition, bool obstacle);
	~Node();
	//void init();
	//void update();
	void display();
	void setStartNode();
	void setFinishNode();
	void calculateNeighbours(Node* node, int neighbourType);
	//GLuint loadPNG(char* name);


	//	bool bObstacle = false;			//Is the node an obstruction?
	bool isVisited = false;			//Have we searched this node before?
	bool isANeighbour = false;
	bool isStartNode = false;
	bool isFinishNode = false;
	bool isObstacle = true;
	int distanceToGoal;
	int distanceToStart;
	int totalFromBoth;
	int width = 40;
	int height = 40;
	int xPosition = 0;
	int yPosition = 0;
	int xPos = 0;
	int yPos = 0;
	int neighbourTopInt = 10;
	int neighbourBottomInt = 10;
	int neighbourLeftInt = 10;
	int neighbourRightInt = 10;
	int neighbourTopLeftInt = 14;
	int neighbourTopRightInt = 14;
	int neighbourBottomLeftInt = 14;
	int neighbourBottomRightInt = 14;
	Node* neighbourTop;
	Node* neighbourBottom;
	Node* neighbourLeft;
	Node* neighbourRight;
	Node* neighbourTopLeft;
	Node* neighbourTopRight;
	Node* neighbourBottomLeft;
	Node* neighbourBottomRight;

};