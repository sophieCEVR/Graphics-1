#include <windows.h>		// Header file for Windows
#include <iostream>
#include <fstream>
#include "Image_Loading/nvImage.h"		//allows use of nvidia image loading header file to load textures 
#include "OBB.h"						//Object Bounding Box header file allows for OBB calculations
#include "Hanzo.h"
#include "Player2Hanzo.h"
#include "Chompsky.h"
#include "Character.h"
#include "dumbAI.h"
#include "FastAI.h"
#include "OppositeAI.h"
#include "Owner.h"
#include "Map.h"
#include "HUD.h"
#include "Node.h"
#include "Menu.h"
#include <Mmsystem.h>
#include <string>
#include <cstdlib>
#include <math.h>			// Header File For Maths Functions
#include <time.h>			// Header File For Clock Functions and Variables

//Screen settings
int screenWidth = 1600, screenHeight = 900;
int innerWidth, innerHeight;
int	mouse_x = 0, mouse_y = 0;
int health = 6;
int health2 = 6;
int boost = 0;
int boost2 = 0;

__int64 prevTime = 0;				// Previous count
// Timer 
// convert clock ticks to time increment suitable for simulation constants
double timerFrequencyRecip = 0.0000005;  // Only needs to be changed to change speed of simulation but is platform independent
// Smaller values will slow down the simulation, larger values will speed it up
double deltaT = 0;
float timer = 0;
float timer2 = 0;

float spin = 0;
float speed = 0; //check if i need this
float XviewZoomout = 4;
float YviewZoomout = 2;

bool gameActive = false;
bool LeftPressed = false;
bool keys[256];
bool twoPlayerGame = false;
bool boostActivated = false;
bool boostActivated2 = false;
bool lastForward = false;
bool lastBackward = false;
bool lastLeft = false;
bool lastRight = false;
bool healthRemoved = false;
bool healthRemovedAI1 = false;
bool healthRemovedAI2 = false;
bool healthRemovedAI3 = false;
bool charBouncedAI1 = false;
bool charBouncedAI2 = false;
bool charBouncedAI3 = false;
bool miniGameBool = false;
bool pancakesClicked = false;
bool cakeClicked = false;
bool doughnutsClicked = false;
bool catClicked = false;
bool miniGameWin = false;
bool miniGameLoss = false;
bool singlePlayer1 = false;
bool singlePlayer2 = false;
bool singlePlayer3 = false;

Menu* menu = new Menu();
Map* map;
Hanzo* player1;
Character* player2;
Chompsky* chompsky;
Character* owner;
HUD* hud;
HUD* hud2;
dumbAI* ai1;
FastAI* ai2;
OppositeAi* ai3;



//OPENGL FUNCTION PROTOTYPES

GLuint loadPNG(char* name);
GLuint miniGameTexture = 0;
GLuint miniGameTextureWin = 0;
GLuint miniGameTextureLoss = 0;

void init();										//called in winmain when the program starts.
void display();										//called in winmain to draw everything to the screen
void update();										//called in winmain to update variables
void reshape(int width, int height);				//called when the window is resized
void processKeys();								    //called in winmain to process keyboard input
void collisionChecking();							//collision handling
void winCondition(int winType);						//method to process different win conditions
void lossCondition(int lossType);					//method to process different loss conditions
void startNewGame();
void miniGameDisplay();
void miniGameUpdate();

GLuint loadPNGMap(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if(!miniGameBool){
		map->display();
		player1->display();
		if (twoPlayerGame) {
			player2->display();
		}
		else {
			chompsky->display();
			owner->display();
			ai1->display();
			ai2->display();
			ai3->display();
		}
	}
	else {
		miniGameDisplay();
	}
}

//updates variables based on user interaction
void update()
{// Get the current time
	if (!miniGameBool) {
		if (health <= 0) {
			lossCondition(1);
		}
		if (gameActive) {
			if (chompsky->chompskyActive) {
				list<MiniGameBarn*> mgList;
				for (MapObject* m : map->objectList) {
					MiniGameBarn* mg = dynamic_cast<MiniGameBarn*>(m);
					if (mg) {
						mgList.push_back(mg);
					}
				}

				for (MiniGameBarn* mg : mgList) {
					mg->objTexture = mg->textureOpen;
				}

			}
			LARGE_INTEGER t;
			QueryPerformanceCounter(&t);
			__int64 currentTime = t.QuadPart;

			__int64 ticksElapsed = currentTime - prevTime;					// Ticks elapsed since the previous time step
			deltaT = double(ticksElapsed) * timerFrequencyRecip;		// Convert to second

			prevTime = currentTime;					// use the current time as the previous time in the next step
			if (player1->spacePressed) {
				boostActivated = true;
				if (!miniGameWin) {
					boost = 0;
				}
				else {
					boost = 3;
				}
			}
			if (boostActivated && timer < 3) {
				timer += deltaT;
			}
			else if (boostActivated && timer >= 3) {
				boostActivated = false;
				player1->spacePressed = false;
				chompsky->spacePressed = false;
				timer = 0;
			}
			//if (twoPlayerGame) {
			//	if (player2->spacePressed) {
			//		boostActivated2 = true;
			//		boost2 = 3;
			//	}
			//	if (boostActivated2 && timer2 < 3) {
			//		timer2 += deltaT;
			//	}
			//	else if (boostActivated2 && timer2 >= 3) {
			//		boostActivated2 = false;
			//		player2->spacePressed = false;
			//		timer2 = 0;
			//	}
			//}
			owner->update(keys);
			player1->update(keys);
			ai1->update(keys);
			ai2->update(keys);
			ai3->update(keys);
			if (twoPlayerGame) {
				player2->update(keys);
			}

			float hanzoX = player1->Xchar;
			float hanzoY = player1->Ychar;
			float player2X;
			float player2Y;
			if (twoPlayerGame) {
				player2X = player2->Xchar;
				player2Y = player2->Ychar;
			}
			if (!twoPlayerGame) {
				chompsky->Xobject = hanzoX;
				chompsky->Yobject = hanzoY;
				chompsky->update(keys);
			}
			hud->update(health, boost, hanzoX, hanzoY, screenWidth, screenHeight);
			if (twoPlayerGame) {
				hud2->update(health2, boost2, hanzoX, hanzoY-700, screenWidth, screenHeight);
			}
			glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
			glLoadIdentity();									// reset the top of the projection matrix to an identity matrix
			Hanzo* hanzoView = dynamic_cast<Hanzo*>(player1);
			if (hanzoView->lead) {
				gluOrtho2D(-screenWidth / 4 + hanzoX, screenWidth / 4 + hanzoX, hanzoY - 300, screenHeight / 2 + (hanzoY - 300));           // set the coordinate system for the window
			}
			else if (XviewZoomout > 2.3) {
				XviewZoomout -= 0.03;
				YviewZoomout -= 0.015;
			}
			//std::cout << YviewZoomout << std::endl;
			//	std::cout << XviewZoomout << std::endl;

			if (!hanzoView->lead) {
				gluOrtho2D(-screenWidth / XviewZoomout + hanzoX, screenWidth / XviewZoomout + hanzoX, hanzoY - 300, screenHeight / YviewZoomout + (hanzoY - 300));
			}

			//if(hanzo->charOBB==CornerPath->objectOBB)

			glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
			glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix

			player1->collideRight = false;
			player1->collideUp = false;
			player1->collideDown = false;
			player1->collideLeft = false;

			chompsky->collideRight = false;
			chompsky->collideUp = false;
			chompsky->collideDown = false;
			chompsky->collideLeft = false;

			if (twoPlayerGame) {
				player2->collideRight = false;
				player2->collideUp = false;
				player2->collideDown = false;
				player2->collideLeft = false;
			}
			collisionChecking();
		}
	}
	else {

	}
}

void processKeys(){
	if (!miniGameBool) {
		if (gameActive) {
			player1->processKeys(keys, boost);
			if (twoPlayerGame) {
				player2->processKeys(keys, boost);
			}
			else {
				chompsky->processKeys(keys, boost);
				owner->processKeys(keys, boost);
			}
		}
	}
}

void init() {
	glClearColor(0.0, 0.5, 0.0, 0.0);
	miniGameTextureWin = loadPNG("textures/menus/miniGameWin.png");
	miniGameTextureLoss = loadPNG("textures/menus/miniGameLoss.png");
	miniGameTexture = loadPNG("textures/menus/miniGame.png");
	reshape(innerWidth, innerHeight);
	menu->init(innerHeight, innerWidth);
}

void startNewGame() {
		map = new Map();
		player1 = new Hanzo();
		player2 = new Player2Hanzo();
		chompsky = new Chompsky();
		owner = new Owner();
		hud = new HUD(health, boost, screenWidth, screenHeight);
		if (twoPlayerGame) {
			hud2 = new HUD(health2, boost2, 0, 0);
		}
		ai1 = new dumbAI();
		ai2 = new FastAI();
		ai3 = new OppositeAi();
		delete menu;
		map->init();
		player1->init();
		player2->init();
		chompsky->init();
		owner->init();
		hud->init();		
		if (twoPlayerGame) {
			hud2->init();
			hud2->setTwoPlayer();
			map->twoPlayerGame = true;
			hud->setTwoPlayer();
		}
		ai1->init();
		ai1->chickenLocation(map->chickenPointer->xItem, map->chickenPointer->yItem);
		ai2->init();
		ai2->chickenLocation(map->chickenPointer->xItem, map->chickenPointer->yItem);
		ai3->init();
		ai3->chickenLocation(map->chickenPointer->xItem, map->chickenPointer->yItem);
		health = 6;
		boost = 0;
		health2 = 6;
		boost2 = 0;
}
void collisionChecking() {
	if (!miniGameBool) {
		/*********************************************************/
						//edge of path collisions
		/*********************************************************/
		list<CornerPath*> cpList;
		for (MapObject* m : map->objectList) {
			CornerPath* cp = dynamic_cast<CornerPath*>(m);
			if (cp) {
				cpList.push_back(cp);
			}
		}

		for (CornerPath* cp : cpList) {
			if (cp->pathOBB.SAT2D((player1->charOBB))) {
				//hanzo->collide = true;
				//glColor3f(1.0, 0.0, 0.0);
				//cp->pathOBB.drawOBB();
				if (cp->charPassed == '[') {//left
					player1->collideLeft = true;
					chompsky->collideLeft = true;
				}
				else if (cp->charPassed == ']') {//right
					player1->collideRight = true;
					chompsky->collideRight = true;
				}
				else if (cp->charPassed == '-') {//top path
					player1->collideUp = true;
					chompsky->collideUp = true;
				}
				else if (cp->charPassed == '~') { //bottom path
					player1->collideDown = true;
					chompsky->collideDown = true;
				}
				else if (cp->charPassed == '`') { //top left corner path
					player1->collideUp = true;
					player1->collideLeft = true;
					chompsky->collideUp = true;
					chompsky->collideLeft = true;
				}
				else if (cp->charPassed == '"') { //top right corner path
					player1->collideUp = true;
					player1->collideRight = true;
					chompsky->collideUp = true;
					chompsky->collideRight = true;
				}
				else if (cp->charPassed == ',') { //bottom left corner
					player1->collideDown = true;
					player1->collideLeft = true;
					chompsky->collideDown = true;
					chompsky->collideLeft = true;
				}
				else if (cp->charPassed == '.') { //bottom right corner
					player1->collideDown = true;
					player1->collideRight = true;
					chompsky->collideDown = true;
					chompsky->collideRight = true;
				}
				if (player1->spacePressed) {

					lastForward = player1->forward;
					lastBackward = player1->backward;
					lastLeft = player1->left;
					lastRight = player1->right;

					LARGE_INTEGER t;
					QueryPerformanceCounter(&t);
					__int64 currentTime = t.QuadPart;

					__int64 ticksElapsed = currentTime - prevTime;					// Ticks elapsed since the previous time step
					deltaT = double(ticksElapsed) * timerFrequencyRecip;			// Convert to second

					prevTime = currentTime;											// use the current time as the previous time in the next step
					if (timer < 3) {
						player1->collisionBoost = true;
						chompsky->collisionBoost = true;
						player1->stunned = true;
						chompsky->stunned = true;
						player1->forward = false;
						chompsky->forward = false;
						player1->backward = false;
						chompsky->backward = false;
						player1->left = false;
						chompsky->left = false;
						player1->right = false;
						chompsky->right = false;

					}
					else if (timer >= 3) {
						player1->collisionBoost = false;
						chompsky->collisionBoost = false;
						player1->stunned = false;
						chompsky->stunned = false;

						player1->forward = lastForward;
						player1->backward = lastBackward;
						player1->left = lastLeft;
						player1->right = lastRight;

						chompsky->forward = lastForward;
						chompsky->backward = lastBackward;
						chompsky->left = lastLeft;
						player1->right = lastRight;

						lastForward = false;
						lastBackward = false;
						lastLeft = false;
						lastRight = false;

						if (!healthRemoved) {
							health = health - 2;
							healthRemoved = true;
						}
					}
				}
				else {
					healthRemoved = false;
					timer = 0;
				}
			}
			if (player1->charOBB.SAT2D(ai1->charOBB)) {
				//glColor3f(1.0, 0.0, 0.0);
				//player1->charOBB.drawOBB();
				//ai1->charOBB.drawOBB();
				if (!charBouncedAI1) {
					player1->Xchar += 05;
					player1->Ychar -= 05;
					charBouncedAI1 = true;
				}
				if (!healthRemovedAI1) {
					health = health - 1;
					healthRemovedAI1 = true;
				}
			}
			else {
				healthRemovedAI1 = false;
				charBouncedAI1 = false;
			}
			if (player1->charOBB.SAT2D(ai2->charOBB)) {
				//glColor3f(1.0, 0.0, 0.0);
				//player1->charOBB.drawOBB();
				//ai2->charOBB.drawOBB();
				if (!charBouncedAI2) {
					player1->Xchar += 05;
					player1->Ychar -= 05;
					charBouncedAI2 = true;
				}
				if (!healthRemovedAI2) {
					health = health - 1;
					healthRemovedAI2 = true;
				}
			}
			else {
				healthRemovedAI2 = false;
				charBouncedAI2 = false;
			}
			if (player1->charOBB.SAT2D(ai3->charOBB)) {
				//glColor3f(1.0, 0.0, 0.0);
				//player1->charOBB.drawOBB();
				//ai3->charOBB.drawOBB();
				if (!charBouncedAI3) {
					player1->Xchar += 05;
					player1->Ychar -= 05;
					charBouncedAI3 = true;
				}
				if (!healthRemovedAI3) {
					health = health - 1;
					healthRemovedAI3 = true;
				}
			}
			else {
				healthRemovedAI3 = false;
				charBouncedAI3 = false;
			}
			/*******************************************************/
						//AI 1 collisions
			/*******************************************************/
			if (cp->pathOBB.SAT2D((ai1->charOBB))) {
				glColor3f(1.0, 0.0, 0.0);
				cp->pathOBB.drawOBB();
				if (cp->charPassed == '[') {//left
					ai1->Xchar += 2;
					ai1->collideLeft = true;
					ai1->collideRight = false;
					ai1->collideUp = false;
					ai1->collideDown = false;
				}
				else if (cp->charPassed == ']') {//right
					ai1->Xchar -= 2;
					ai1->collideRight = true;
					ai1->collideLeft = false;
					ai1->collideUp = false;
					ai1->collideDown = false;
				}
				else if ((cp->charPassed == '-') && !(cp->charPassed == '[') && !(cp->charPassed == '`')) {//top path
					ai1->Ychar -= 2;
					ai1->collideUp = true;
					//ai1->collideLeft = false;
					ai1->collideRight = false;
					ai1->collideDown = false;
				}
				else if ((cp->charPassed == '-') && (cp->charPassed == '[') && !(cp->charPassed == '`')) {
					ai1->Ychar -= 2;
					ai1->collideUp = true;
					ai1->collideLeft = true;
					ai1->collideRight = false;
					ai1->collideDown = false;
				}
				else if ((cp->charPassed == '-') && (cp->charPassed == '[') && (cp->charPassed == '`')) {
					ai1->Ychar -= 2;
					ai1->collideUp = true;
					ai1->collideLeft = true;
					ai1->collideRight = false;
					ai1->collideDown = false;
				}
				else if ((cp->charPassed == '-') && !(cp->charPassed == '[') && (cp->charPassed == '`')) {
					ai1->Ychar -= 2;
					ai1->collideUp = true;
					ai1->collideLeft = true;
					ai1->collideRight = false;
					ai1->collideDown = false;
				}
				else if (cp->charPassed == '~') { //bottom path
					ai1->collideDown = true;
					ai1->collideLeft = false;
					ai1->collideRight = false;
					ai1->collideUp = false;
				}
				else if (cp->charPassed == '`') { //top left corner path
					ai1->collideUp = true;
					ai1->collideLeft = true;
					//ai1->collideRight = false;
					//ai1->collideDown = false;
				}
				else if (cp->charPassed == '"') { //top right corner path
					ai1->collideUp = true;
					ai1->collideRight = true;
					//ai1->collideLeft = false;
					//ai1->collideDown = false;
				}
				else if (cp->charPassed == ',') { //bottom left corner
					ai1->collideDown = true;
					ai1->collideLeft = true;
					//ai1->collideUp = false;
					//ai1->collideRight = false;
				}
				else if (cp->charPassed == '.') { //bottom right corner
					ai1->collideDown = true;
					ai1->collideRight = true;
					//ai1->collideUp = false;
					//ai1->collideLeft = false;
				}
			}
			//else {
			//	ai1->collideUp = true;
			//	ai1->collideLeft = true;
			//	ai1->collideDown = true;
			//	ai1->collideRight = true;
			//}
			/*******************************************************/
							//AI 2 collisions
			/*******************************************************/
			if (cp->pathOBB.SAT2D((ai2->charOBB))) {
				glColor3f(1.0, 0.0, 0.0);
				cp->pathOBB.drawOBB();
				if (cp->charPassed == '[') {//left
					ai2->Xchar += 2;
					ai2->collideLeft = true;
					ai2->collideRight = false;
					ai2->collideUp = false;
					ai2->collideDown = false;
				}
				else if (cp->charPassed == ']') {//right
					ai2->Xchar -= 2;
					ai2->collideRight = true;
					ai2->collideLeft = false;
					ai2->collideUp = false;
					ai2->collideDown = false;
				}
				else if ((cp->charPassed == '-') && !(cp->charPassed == '[') && !(cp->charPassed == '`')) {//top path
					ai2->Ychar -= 2;
					ai2->collideUp = true;
					//ai1->collideLeft = false;
					ai2->collideRight = false;
					ai2->collideDown = false;
				}
				else if ((cp->charPassed == '-') && (cp->charPassed == '[') && !(cp->charPassed == '`')) {
					ai2->Ychar -= 2;
					ai2->collideUp = true;
					ai2->collideLeft = true;
					ai2->collideRight = false;
					ai2->collideDown = false;
				}
				else if ((cp->charPassed == '-') && (cp->charPassed == '[') && (cp->charPassed == '`')) {
					ai2->Ychar -= 2;
					ai2->collideUp = true;
					ai2->collideLeft = true;
					ai2->collideRight = false;
					ai2->collideDown = false;
				}
				else if ((cp->charPassed == '-') && !(cp->charPassed == '[') && (cp->charPassed == '`')) {
					ai2->Ychar -= 2;
					ai2->collideUp = true;
					ai2->collideLeft = true;
					ai2->collideRight = false;
					ai2->collideDown = false;
				}
				else if (cp->charPassed == '~') { //bottom path
					ai2->collideDown = true;
					ai2->collideLeft = false;
					ai2->collideRight = false;
					ai2->collideUp = false;
				}
				else if (cp->charPassed == '`') { //top left corner path
					ai2->collideUp = true;
					ai2->collideLeft = true;
					//ai1->collideRight = false;
					//ai1->collideDown = false;
				}
				else if (cp->charPassed == '"') { //top right corner path
					ai2->collideUp = true;
					ai2->collideRight = true;
					//ai1->collideLeft = false;
					//ai1->collideDown = false;
				}
				else if (cp->charPassed == ',') { //bottom left corner
					ai2->collideDown = true;
					ai2->collideLeft = true;
					//ai1->collideUp = false;
					//ai1->collideRight = false;
				}
				else if (cp->charPassed == '.') { //bottom right corner
					ai2->collideDown = true;
					ai2->collideRight = true;
					//ai1->collideUp = false;
					//ai1->collideLeft = false;
				}
			}
			//else {
			//	ai1->collideUp = true;
			//	ai1->collideLeft = true;
			//	ai1->collideDown = true;
			//	ai1->collideRight = true;
			//}
			/*******************************************************/
							//AI 3 collisions
			/*******************************************************/
			if (cp->pathOBB.SAT2D((ai3->charOBB))) {
				glColor3f(1.0, 0.0, 0.0);
				cp->pathOBB.drawOBB();
				if (cp->charPassed == '[') {//left
					ai3->Xchar += 2;
					ai3->collideLeft = true;
					ai3->collideRight = false;
					ai3->collideUp = false;
					ai3->collideDown = false;
				}
				else if (cp->charPassed == ']') {//right
					ai3->Xchar -= 2;
					ai3->collideRight = true;
					ai3->collideLeft = false;
					ai3->collideUp = false;
					ai3->collideDown = false;
				}
				else if ((cp->charPassed == '-') && !(cp->charPassed == '[') && !(cp->charPassed == '`')) {//top path
					ai3->Ychar -= 2;
					ai3->collideUp = true;
					//ai1->collideLeft = false;
					ai3->collideRight = false;
					ai3->collideDown = false;
				}
				else if ((cp->charPassed == '-') && (cp->charPassed == '[') && !(cp->charPassed == '`')) {
					ai3->Ychar -= 2;
					ai3->collideUp = true;
					ai3->collideLeft = true;
					ai3->collideRight = false;
					ai3->collideDown = false;
				}
				else if ((cp->charPassed == '-') && (cp->charPassed == '[') && (cp->charPassed == '`')) {
					ai3->Ychar -= 2;
					ai3->collideUp = true;
					ai3->collideLeft = true;
					ai3->collideRight = false;
					ai3->collideDown = false;
				}
				else if ((cp->charPassed == '-') && !(cp->charPassed == '[') && (cp->charPassed == '`')) {
					ai3->Ychar -= 2;
					ai3->collideUp = true;
					ai3->collideLeft = true;
					ai3->collideRight = false;
					ai3->collideDown = false;
				}
				else if (cp->charPassed == '~') { //bottom path
					ai3->collideDown = true;
					ai3->collideLeft = false;
					ai3->collideRight = false;
					ai3->collideUp = false;
				}
				else if (cp->charPassed == '`') { //top left corner path
					ai3->collideUp = true;
					ai3->collideLeft = true;
					//ai1->collideRight = false;
					//ai1->collideDown = false;
				}
				else if (cp->charPassed == '"') { //top right corner path
					ai3->collideUp = true;
					ai3->collideRight = true;
					//ai1->collideLeft = false;
					//ai1->collideDown = false;
				}
				else if (cp->charPassed == ',') { //bottom left corner
					ai3->collideDown = true;
					ai3->collideLeft = true;
					//ai1->collideUp = false;
					//ai1->collideRight = false;
				}
				else if (cp->charPassed == '.') { //bottom right corner
					ai3->collideDown = true;
					ai3->collideRight = true;
					//ai1->collideUp = false;
					//ai1->collideLeft = false;
				}
			}
			//else {
			//	ai1->collideUp = true;
			//	ai1->collideLeft = true;
			//	ai1->collideDown = true;
			//	ai1->collideRight = true;
			//}

			/***************************************************/
							//2 player collisions
			/***************************************************/
			if (twoPlayerGame) {
				if (cp->pathOBB.SAT2D((player2->charOBB))) {
					//hanzo->collide = true;
					if (cp->charPassed == '[') {//left
						player2->collideLeft = true;
					}
					else if (cp->charPassed == ']') {//right
						player2->collideRight = true;
					}
					else if (cp->charPassed == '-') {//top path
						player2->collideUp = true;
					}
					else if (cp->charPassed == '~') { //bottom path
						player2->collideDown = true;
					}
					else if (cp->charPassed == '`') { //top left corner path
						player2->collideUp = true;
						player2->collideLeft = true;
					}
					else if (cp->charPassed == '"') { //top right corner path
						player2->collideUp = true;
						player2->collideRight = true;
					}
					else if (cp->charPassed == ',') { //bottom left corner
						player2->collideDown = true;
						player2->collideLeft = true;
					}
					else if (cp->charPassed == '.') { //bottom right corner
						player2->collideDown = true;
						player2->collideRight = true;
					}
					if (player2->spacePressed) {

						lastForward = player2->forward;
						lastBackward = player2->backward;
						lastLeft = player2->left;
						lastRight = player2->right;

						LARGE_INTEGER t;
						QueryPerformanceCounter(&t);
						__int64 currentTime = t.QuadPart;

						__int64 ticksElapsed = currentTime - prevTime;					// Ticks elapsed since the previous time step
						deltaT = double(ticksElapsed) * timerFrequencyRecip;			// Convert to second

						prevTime = currentTime;											// use the current time as the previous time in the next step
						if (timer < 3) {
							player2->collisionBoost = true;
							player2->stunned = true;
							player2->forward = false;
							player2->backward = false;
							player2->left = false;
							player2->right = false;

						}
						else if (timer >= 3) {
							player2->collisionBoost = false;
							player2->stunned = false;

							player2->forward = lastForward;
							player2->backward = lastBackward;
							player2->left = lastLeft;
							player2->right = lastRight;

							player2->right = lastRight;

							lastForward = false;
							lastBackward = false;
							lastLeft = false;
							lastRight = false;

							if (!healthRemoved) {
								health2 = health2 - 2;
								healthRemoved = true;
							}
						}
					}
					else {
						healthRemoved = false;
						timer = 0;
					}
				}
			}
		}


		/*********************************************************/
							//MiniGameBarn collisions
		/*********************************************************/

		list<MiniGameBarn*> mgList;
		for (MapObject* m : map->objectList) {
			MiniGameBarn* mg = dynamic_cast<MiniGameBarn*>(m);
			if (mg) {
				mgList.push_back(mg);
			}
		}
		for (MiniGameBarn* mg : mgList) {
			if (mg->mgOBB.SAT2D((player1->charOBB)) && chompsky->chompskyActive) {
				//mg->mgOBB.drawOBB();
				miniGameBool = true;
				PlaySound("audio/dogNoise.wav", NULL, SND_ASYNC);
				miniGameDisplay();
				//glColor3f(1.0, 0.0, 0.0);
			}
			if (mg->mgOBB.SAT2D((player1->charOBB)) && !chompsky->chompskyActive) {
				player1->collideUp = true;
				//mg->mgOBB.drawOBB();
			//	glColor3f(1.0, 0.0, 0.0);
			}
		}
		/*********************************************************/
							//item collisions
		/*********************************************************/

		//heart collision 
		list<Heart*> hList;
		for (Item* i : map->itemList) {
			Heart* h = dynamic_cast<Heart*>(i);
			if (h) {
				hList.push_back(h);
			}
		}

		for (Heart* h : hList) {
			if (h->itemOBB.SAT2D((player1->charOBB))) {
				if (health < 6) {
					health++;
				}
				h->~Heart();
			}

			if (twoPlayerGame) {
				if (h->itemOBB.SAT2D((player2->charOBB))) {
					if (health2 < 6) {
						health2++;
					}
					h->~Heart();
				}
			}
		}
		//bone collision 
		list<Bone*> bList;
		for (Item* i : map->itemList) {
			Bone* b = dynamic_cast<Bone*>(i);
			if (b) {
				bList.push_back(b);
			}
		}

		for (Bone* b : bList) {
			if (b->itemOBB.SAT2D((player1->charOBB))) {
				if (boost != 3) {
					boost++;
				}
				b->~Bone();
			}
			if (twoPlayerGame) {
				if (b->itemOBB.SAT2D((player2->charOBB))) {
					if (boost2 != 3) {
						boost2++;
					}
					b->~Bone();
				}
			}
		}


		//Chicken collision 
		if (map->chickenPointer->itemOBB.SAT2D((player1->charOBB))) {
			glColor3f(1.0, 0.0, 0.0);
			map->chickenPointer->itemOBB.drawOBB();
			winCondition(1);
		}
		else if (map->chickenPointer->itemOBB.SAT2D((ai1->charOBB))) {
			glColor3f(1.0, 0.0, 0.0);
			map->chickenPointer->itemOBB.drawOBB();
			lossCondition(2);
		}
		else if (map->chickenPointer->itemOBB.SAT2D((ai2->charOBB))) {
			glColor3f(1.0, 0.0, 0.0);
			map->chickenPointer->itemOBB.drawOBB();
			lossCondition(2);
		}
		else if (twoPlayerGame) {
			if ((map->chickenPointer->itemOBB.SAT2D((player2->charOBB)))) {
				glColor3f(0.0, 1.0, 0.0);
				map->chickenPointer->itemOBB.drawOBB();
				winCondition(2);
			}
		}
		 
	}
}

void winCondition(int winType) {
	gameActive = false;
	delete map;
	delete player1;
	delete player2;
	delete chompsky;
	delete owner;
	delete ai1;
	delete ai2;
	menu = new Menu();
	menu->init(screenHeight, screenWidth);
	if (winType == 1 && !twoPlayerGame) {//player 1 got the chicken 
		cout << "you got the chicken!" << endl;
		menu->outcomeCard = 1;
	}
	//if (winType == 1 && twoPlayerGame) {//player 1 got the chicken playing 2 player mode
	//	cout << "Player 1 beat player 2 !" << endl;
	//}
	//if (winType == 2) {//player 2 got the chicken playing 2 player mode
	//	cout << "Player 2 beat player 1 !" << endl;
	//}
	menu->display(screenHeight, screenWidth);
}

void lossCondition(int lossType) {
	gameActive = false;
	delete map;
	delete player1;
	delete player2;
	delete chompsky;
	delete owner;
	delete ai1;
	menu = new Menu();
	menu->init(screenHeight, screenWidth);
	if (lossType == 1 && !twoPlayerGame) {//player 1 got the chicken 
		menu->outcomeCard = 2;
	}
	else if (lossType == 2 && !twoPlayerGame) {//player 1 got the chicken 
		menu->outcomeCard = 3;
	}
	menu->display(screenHeight, screenWidth);
}

void miniGameDisplay() {
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor3f(1.0, 1.0, 0.0);
		glEnable(GL_TEXTURE_2D);

		if (!miniGameWin && !miniGameLoss && miniGameBool) {
			glBindTexture(GL_TEXTURE_2D, miniGameTexture);
		}
		else if (miniGameLoss && !miniGameWin && miniGameBool) {
			glBindTexture(GL_TEXTURE_2D, miniGameTextureLoss);
		}
		else if (!miniGameLoss && miniGameWin && miniGameBool) {
			glBindTexture(GL_TEXTURE_2D, miniGameTextureWin);
		}
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex2f(-screenWidth / 4, 0);
			glTexCoord2f(0.0, 1.0); glVertex2f(-screenWidth / 4, screenHeight / 2);
			glTexCoord2f(1.0, 1.0); glVertex2f(screenWidth / 4, screenHeight / 2);
			glTexCoord2f(1.0, 0.0); glVertex2f(screenWidth / 4, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void miniGameUpdate() {
	std::cout << "mouseX : " << mouse_x << "     mouseY : " << mouse_y << std::endl;
	if (catClicked) {
		miniGameLoss = true;
		if ((mouse_x > 860 && mouse_x < 1560) && (mouse_y > 110 && mouse_y < 265) && LeftPressed) {
			chompsky->Xchar = 0;
			chompsky->Ychar = 0;
			chompsky->chompskyActive = false;
			chompsky->chompskyInPlace = false;
			miniGameBool = false;

			catClicked = false;
			pancakesClicked = false;
			cakeClicked = false;
			doughnutsClicked = false;

			PlaySound("audio/Metal_Race.wav", NULL, SND_ASYNC);
			player1->Ychar = player1->Ychar - 2; 
			list<MiniGameBarn*> mgList;
			for (MapObject* m : map->objectList) {
				MiniGameBarn* mg = dynamic_cast<MiniGameBarn*>(m);
				if (mg) {
					mgList.push_back(mg);
				}
			}

			for (MiniGameBarn* mg : mgList) {
				mg->objTexture = map->miniGameBarnClosed;
			}
		}
	}
	else if (pancakesClicked && cakeClicked && doughnutsClicked) {
		miniGameWin = true;
		if ((mouse_x > 110 && mouse_x < 820) && (mouse_y > 25 && mouse_y < 150) && LeftPressed) {
			chompsky->Xchar = 0;
			chompsky->Ychar = 0;
			chompsky->chompskyActive = false;
			chompsky->chompskyInPlace = false;
			

			catClicked = false;
			pancakesClicked = false;
			cakeClicked = false;
			doughnutsClicked = false;


			boost = 3;
			miniGameBool = false;
			PlaySound("audio/Metal_Race.wav", NULL, SND_ASYNC);
			player1->Ychar = player1->Ychar - 2;
			list<MiniGameBarn*> mgList;
			for (MapObject* m : map->objectList) {
				MiniGameBarn* mg = dynamic_cast<MiniGameBarn*>(m);
				if (mg) {
					mgList.push_back(mg);
				}
			}

			for (MiniGameBarn* mg : mgList) {
				mg->objTexture = map->miniGameBarnClosed;
			}

		}
	}
	else {
		if ((mouse_x > 585 && mouse_x < 945) && (mouse_y > 355 && mouse_y < 710) && LeftPressed) {
			std::cout << "pancakesClicked" << std::endl;
			pancakesClicked = true;
		}
		else if ((mouse_x > 520 && mouse_x < 950) && (mouse_y > 90 && mouse_y < 330) && LeftPressed) {
			std::cout << "cakeClicked" << std::endl;
			cakeClicked = true;
		}
		else if ((mouse_x > 990 && mouse_x < 1490) && (mouse_y > 135 && mouse_y < 345) && LeftPressed) {
			std::cout << "doughnutsClicked" << std::endl;
			doughnutsClicked = true;
		}
		else if ((mouse_x > 990 && mouse_x < 1450) && (mouse_y > 355 && mouse_y < 710) && LeftPressed) {
			std::cout << "catClicked" << std::endl;
			catClicked = true;
		}
	}
}

/*************    START OF OPENGL FUNCTIONS   ****************/
void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;           // to ensure the mouse coordinates match 

	glViewport(0, 0, width, height);						// Reset the current viewport
	
		//glViewport(width/2, 0, width, height);						// Reset the current viewport
		//glViewport(0, 0, width/2, height);						// Reset the current viewport
	

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(-screenWidth / 4, screenWidth / 4, 0, screenHeight / 2);           // set the coordinate system for the window
	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}


//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done=false;								// Bool Variable To Exit Loop


	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example",screenWidth,screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (menu->quit && !gameActive)
				done = true;
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if(keys[VK_ESCAPE])
				done = true;

			processKeys();			//process keyboard
			
			if (gameActive) {
				if (miniGameBool) {
					reshape(screenWidth, screenHeight);
				}
				if (miniGameBool) {
					miniGameUpdate();					// update variables
				}
				display();					// Draw The Scene

				if(!miniGameBool) {
					update();					// update variables
				}
			}
			else {
				reshape(screenWidth, screenHeight);
				menu->display(screenHeight, screenWidth);
				menu->update(mouse_x, mouse_y, LeftPressed);
				gameActive = menu->singlePlayerActivated;
				twoPlayerGame = menu->twoPlayerActivated;
				singlePlayer1 = menu->oneAIActivated;
				singlePlayer2 = menu->twoAIPlayerActivated;
				singlePlayer3 = menu->threeAIPlayerActivated;
				if (gameActive) {
					menu->singlePlayerActivated = false;
					menu->twoPlayerActivated = false;
					menu->oneAIActivated = false;
					menu->twoAIPlayerActivated = false;
					menu->threeAIPlayerActivated = false;
					PlaySound("audio/Metal_Race.wav", NULL, SND_ASYNC);
					miniGameLoss = false;
					miniGameWin = false;
					startNewGame();
				}
			}
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			reshape(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;

		case WM_LBUTTONDOWN:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight - HIWORD(lParam);
				LeftPressed = true;
			}
		break;

		case WM_LBUTTONUP:
			{
	            LeftPressed = false;
			}
		break;

		case WM_MOUSEMOVE:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight  - HIWORD(lParam);
			}
		break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/
 
bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen
	innerWidth = width;
	innerHeight = height;
	init();
	
	return true;									// Success
}
