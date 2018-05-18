#include "Owner.h"



Owner::Owner()
{
	Xchar = 303;						//starting x position for specified character
	Ychar = 155;						//starting y position for specified character
	Xfb1 = 22.5;							//X axis int #1 when facing forward/backwards
	Xfb2 = 22.5;							//X axis int #2 when facing forward/backwards
	Yfb1 = 52.5;							//y axis int #1 when facing forward/backwards
	Yfb2 = 52.5;							//y axis int #2 when facing forward/backwards
	Xlr1 = 22.5;							//X axis int #1 when facing left/right
	Xlr2 = 22.5;							//X axis int #2 when facing left/right
	Ylr1 = 52.5;							//y axis int #1 when facing left/right
	Ylr2 = 52.5;							//y axis int #2 when facing left/right
}


Owner::~Owner(){}

void Owner::additionalDisplay()
{
	/**********************************************************************************************/
										//OBB for all directions
	/**********************************************************************************************/

	if (forward || backward) {
		charOBB.vertOriginal[0].x = -Xfb1;
		charOBB.vertOriginal[0].y = -Yfb1;

		charOBB.vertOriginal[1].x = -Xfb2;
		charOBB.vertOriginal[1].y = Yfb2;

		charOBB.vertOriginal[2].x = Xfb2;
		charOBB.vertOriginal[2].y = Yfb2;

		charOBB.vertOriginal[3].x = Xfb1;
		charOBB.vertOriginal[3].y = -Yfb1;
	}
	else {
		charOBB.vertOriginal[0].x = -Xlr1;
		charOBB.vertOriginal[0].y = -Ylr1;

		charOBB.vertOriginal[1].x = -Xlr1;
		charOBB.vertOriginal[1].y = Ylr2;

		charOBB.vertOriginal[2].x = Xlr2;
		charOBB.vertOriginal[2].y = Ylr2;

		charOBB.vertOriginal[3].x = Xlr2;
		charOBB.vertOriginal[3].y = -Ylr1;
	}
}


void Owner::init()
{
	//glClearColor(0.0, 0.5, 0.0, 0.0);{

	Xchar = 100;						//starting x position for specified character
	Ychar = 100;					//starting y position for specified character
	forward = false;					//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.
	backward = true;					//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.
	left = false;						//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.
	right = false;						//preset to false, will be true when a key has been pressed which moves the character this direction. Used in texture control.

	/********************************Owner png loading**************************************/

	//Owner walking forward
	f1 = loadPNG("textures/Owner/f1.png");
	f2 = loadPNG("textures/Owner/f2.png");
	f3 = loadPNG("textures/Owner/f3.png");
	f4 = loadPNG("textures/Owner/f4.png");
	//Owner walking backwards
	b1 = loadPNG("textures/Owner/b1.png");
	b2 = loadPNG("textures/Owner/b2.png");
	b3 = loadPNG("textures/Owner/b3.png");
	b4 = loadPNG("textures/Owner/b4.png");
	//Owner walking left
	l1 = loadPNG("textures/Owner/l1.png");
	l2 = loadPNG("textures/Owner/l2.png");
	l3 = loadPNG("textures/Owner/l3.png");
	l4 = loadPNG("textures/Owner/l4.png");
	//Owner walking right
	r1 = loadPNG("textures/Owner/r1.png");
	r2 = loadPNG("textures/Owner/r2.png");
	r3 = loadPNG("textures/Owner/r3.png");
	r4 = loadPNG("textures/Owner/r4.png");

	/**********************************************************************************************/
										//OBB init
	/**********************************************************************************************/

	charOBB.vertOriginal[0].x = -Xfb1;
	charOBB.vertOriginal[0].y = -Yfb1;

	charOBB.vertOriginal[1].x = -Xfb2;
	charOBB.vertOriginal[1].y = Yfb2;

	charOBB.vertOriginal[2].x = Xfb2;
	charOBB.vertOriginal[2].y = Yfb2;

	charOBB.vertOriginal[3].x = Xfb1;
	charOBB.vertOriginal[3].y = -Yfb1;
}



//
//void Owner::aStar() {
//
//
//	//Psuedocode
//	OPEN list // the set of nodes to be evaluated 
//	CLOSED list // the set of nodes already evaluated 
//	add the start node to OPEN 
//
//	loop 
//		current = node in OPEN with the lowest F_COST
//		remove current from OPEN 
//		add current to CLOSED
//
//		if current is the target node//path has been found
//			return
//		for each neighbour of the current node
//			if neighbour is not traversable or neighbour is in CLOSED
//				skip to the next neighbour
//
//			if new path to neighbour is shorter OR neighbour is not in OPEN 
//				set F_COST of neighbour
//				set parent of neighbour to current
//				if neighbour is not in OPEN 
//					add neighbour to OPEN
//
//	//notes
//	list
//		Open List () - nodes which need to be checked
//		Closed list () = nodes which have been checked
//	Node
//		h cost (Heuristic) - distance from a node to the target node (use my distance calculator)
//		G cost(distance from staarting node) 
//		F cost (G+H)
//		Parent (Nodes required to reach this node)
//
//	chooses the one with the lowest Fcost to look at first
//}