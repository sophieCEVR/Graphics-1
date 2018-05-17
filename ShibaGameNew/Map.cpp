#include "Map.h"
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

using namespace std;

GLuint Map::loadPNGMap(char* name)
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

GLuint Map::loadPNG(char* name)
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}

void Map::display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	/**********************************************************************************************/
	//Scenery/Map Generator 
	/**********************************************************************************************/
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, background);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0.0); glVertex2f(-800, -400);
		glTexCoord2f(0, 8); glVertex2f(-800, 6400);
		glTexCoord2f(8, 8); glVertex2f(6400, 6400);
		glTexCoord2f(8, 0.0); glVertex2f(6400, -400);
	glEnd();
	/********Texture Ending ***********/
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	for (MapObject*m : objectList) {
		m->display();
	}

	for (Item *i : itemList) {
		i->display();
	}

	for (Node *n : nodeVector) {
		n->display();
	}
}

void Map::mapGenerator() {
	int lineCount = 1;
	int chickenX = 0;
	int notPath = 0;
	string currentLine = "";
	ifstream myfile("MapTexts/map1.txt");
	bool alreadySet = false;
	if (myfile.is_open())
	{
		while (myfile.peek() != EOF)
		{
			getline(myfile, currentLine);
			for(int i = 1; i<137;i++){

			//	nodeVector.push_back(new Node(i, lineCount));
				bool pathFound = false;
				randomize++;
				srand((time(NULL)*i)*(time(NULL)*randomize));
				sleep_for(nanoseconds(10));
				if (currentLine[i] == 'h') {
					objectList.push_back(new House(i, lineCount, housesVector.at(rand() % housesVector.size())));
					i+=7;
				}
				else if (currentLine[i] == 'm') {//miniGameBarn
					objectList.push_back(new MiniGameBarn(i, lineCount, miniGameBarnClosed));
					i += 7;
				}
				else if (currentLine[i] == 'b') {
					objectList.push_back(new Bush(i, lineCount, bushVector.at(rand() % bushVector.size())));
				}
				else if (currentLine[i] == 'p') {
					nodeVector.push_back(new Node(i, lineCount, false));
					if (lineCount == 1 && !alreadySet) {
						nodeVector.at(i-1)->isStartNode = true;
						alreadySet = true;
					}
					objectList.push_back(new Path(i, lineCount, pathVector.at(rand() % pathVector.size())));
					chickenX = i;
				}
				else if (currentLine[i] == '-') {//top path
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(0)));
				}
				else if (currentLine[i] == '~') {//bottom path
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(1)));
				}
				else if (currentLine[i] == '[') {//left path
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(2)));
				} 
				else if (currentLine[i] == ']') {//right path
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(3)));
				}
				else if (currentLine[i] == '`') {//top left corner path
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(4)));
				}
				else if (currentLine[i] == '"') {//top right corner path
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(5)));
				}
				else if (currentLine[i] == ',') {//bottom left corner
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(6)));
				}
				else if (currentLine[i] == '.') {//bottom right corner
					objectList.push_back(new CornerPath(currentLine[i], i, lineCount, cornerPathVector.at(7)));
				}
				if (pathFound = false) {
					notPath++;
				}
				if (currentLine[i] != 'p') {
					nodeVector.push_back(new Node(i, lineCount, true));
				}
			}
			lineCount++;
		}
		if (chickenX % 2 != 0) {
			chickenX++;
		}
		chickenPointer = new Chicken((chickenX/2)+notPath, lineCount-1, chicken);
		nodeVector.at(((chickenX / 2) + notPath)+((lineCount-5)*137)-94)->isFinishNode = true; //what????????????????????????????????????????????????????????????????????????
		itemList.push_back(chickenPointer);
		myfile.close();
	}
	list<Path*> pList;
	for (MapObject* m : objectList) {
		Path* p = dynamic_cast<Path*>(m);
		if (p) {
			pList.push_back(p);
		}
	}

	for (Path* p : pList) {
		if (p->yPosition > 7) {
			int chance = (rand() % 1);
			if (chance == 0) {
				itemList.push_back(new Bone(p->xPosition, p->yPosition, bone));
			}
			/*else if (chance == 10) {
				itemList.push_back(new Heart(p->xPosition, p->yPosition, heart));
			}*/
		}
	}
	for (MapObject* m : objectList) {
		MiniGameBarn* mg = dynamic_cast<MiniGameBarn*>(m);
		if (mg) {
			mg->importOpenTexture(miniGameBarnOpen);
		}
	}
}

void Map::init()
{
	background = loadPNGMap("textures/background.png");
	for (int i = 1; i < 26; i++) {
		std::string textureSourceHouses = "textures/Houses/" + to_string(i) + ".png";
		char char_array_houses[23];
		strcpy(char_array_houses, textureSourceHouses.c_str());
		housesVector.push_back(house = loadPNG(char_array_houses));
	}
	for (int i = 1; i < 7; i++) {
		std::string textureSourceBush = "textures/Bushes/" + to_string(i) + ".png";
		char char_array_bush[23];
		strcpy(char_array_bush, textureSourceBush.c_str());
		bushVector.push_back(bush = loadPNG(char_array_bush));
	}
	for (int i = 1; i < 26; i++) {
		std::string textureSourcePath = "textures/Path/" + to_string(i) + ".png";
		char char_array_path[21];
		strcpy(char_array_path, textureSourcePath.c_str());
		pathVector.push_back(bush = loadPNG(char_array_path));
	}
	for (int i = 1; i < 9; i++) {
		std::string textureSourceCPath = "textures/CornerPath/" + to_string(i) + ".png";
		char char_array_cpath[27];
		strcpy(char_array_cpath, textureSourceCPath.c_str());
		cornerPathVector.push_back(bush = loadPNG(char_array_cpath));
	}

	miniGameBarnClosed = loadPNG("textures/MinigameBarns/Closed.png");
	miniGameBarnOpen = loadPNG("textures/MinigameBarns/Open.png");
	bone = loadPNG("textures/Items/bone.png");
	chicken = loadPNG("textures/Items/chicken.png");
	heart = loadPNG("textures/Items/heart.png");

	mapGenerator();

	for (MapObject*m : objectList) {
		m->init();
	}

	for (Item *i : itemList) {
		i->init();
	}

}

Map::Map(){}


Map::~Map(){}
