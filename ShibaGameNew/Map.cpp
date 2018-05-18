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
			bool pathFound = false;
			notPath = 0;
			getline(myfile, currentLine);
			for(int i = 1; i<charsInFile;i++){

			//	nodeVector.push_back(new Node(i, lineCount));

				if (currentLine[i] != 'p') {
					nodeVector.push_back(new Node(i, lineCount, true));
				}
				randomize++;
				srand((time(NULL)*i)*(time(NULL)*randomize));
				sleep_for(nanoseconds(10));
				if (currentLine[i] == 'h') {
					objectList.push_back(new House(i, lineCount, housesVector.at(rand() % housesVector.size())));
					nodeVector.push_back(new Node(i+1, lineCount, true));
					nodeVector.push_back(new Node(i+2, lineCount, true));
					nodeVector.push_back(new Node(i+3, lineCount, true));
					nodeVector.push_back(new Node(i+4, lineCount, true));
					nodeVector.push_back(new Node(i+5, lineCount, true));
					nodeVector.push_back(new Node(i + 6, lineCount, true));
					nodeVector.push_back(new Node(i + 7, lineCount, true));
					nodeVector.push_back(new Node(i + 8, lineCount, true));
					i+=7;
				}
				else if (currentLine[i] == 'm') {//miniGameBarn
					objectList.push_back(new MiniGameBarn(i, lineCount, miniGameBarnClosed));
					nodeVector.push_back(new Node(i + 1, lineCount, true));
					nodeVector.push_back(new Node(i + 2, lineCount, true));
					nodeVector.push_back(new Node(i + 3, lineCount, true));
					nodeVector.push_back(new Node(i + 4, lineCount, true));
					nodeVector.push_back(new Node(i + 5, lineCount, true));
					nodeVector.push_back(new Node(i + 6, lineCount, true));
					nodeVector.push_back(new Node(i + 7, lineCount, true));
					nodeVector.push_back(new Node(i + 8, lineCount, true));
					i += 7;
				}
				else if (currentLine[i] == 'b') {
					objectList.push_back(new Bush(i, lineCount, bushVector.at(rand() % bushVector.size())));
				}
				else if (currentLine[i] == 'p') {
					pathFound = true;
					nodeVector.push_back(new Node(i, lineCount, false));
					if (lineCount == 1 && !alreadySet) {
						nodeVector.at(i-1)->isStartNode = true;
						alreadySet = true;
					}
					objectList.push_back(new Path(i, lineCount, pathVector.at(rand() % pathVector.size())));
					chickenX = i-1;
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
				if (pathFound == false) {
					notPath++;
				}
			}
			lineCount++;
		}
		if (chickenX % 2 != 0) {
			chickenX++;
		}
		chickenPointer = new Chicken((chickenX/2)+notPath, lineCount-1, chicken);
		//std::cout << "chickenX : " << chickenX << " notPath : " << notPath << " lineCount : " << lineCount << std::endl;
		nodeVector.at(((chickenX / 2) )+(135*(lineCount-1)))->isFinishNode = true;
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
			int chance = (rand() % 120);
			if (chance == 20) {
				if (!twoPlayerGame) {
					itemList.push_back(new Bone(p->xPosition, p->yPosition, bone));
				}
			}
			else if (chance == 10) {
				itemList.push_back(new Heart(p->xPosition, p->yPosition, heart));
			}
		}
	}
	for (MapObject* m : objectList) {
		MiniGameBarn* mg = dynamic_cast<MiniGameBarn*>(m);
		if (mg) {
			mg->importOpenTexture(miniGameBarnOpen);
		}
	}
	int hi = 1;
	//for (Node* n : nodeVector) {
	//	//for (int i = 0; i < 1; i++) {
	//	hi++;
	//		if (n->xPosition + 200 < nodeVector.size()) {
	//		//	if (i == 0) {
	//				n->calculateNeighbours(nodeVector.at((n->xPosition-1 + 135)), 1);
	//		//	}
	//				cout << "Node number : " << hi << endl;//" node top neighbour " << n->neighbourTop->xPosition-1 << endl;
	//		}
	//	//}
	//}
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
	objectList.push_back(new House(-11, 81, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(12, 81, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(12, 72, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(2, 75, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new Bush(1, 75, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(1, 74, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(10, 75, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(11, 75, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(11, 74, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new CornerPath('`', 2, 74, cornerPathVector.at(4)));
	objectList.push_back(new CornerPath('-', 3, 74, cornerPathVector.at(0)));
	objectList.push_back(new CornerPath('-', 4, 74, cornerPathVector.at(0)));
	objectList.push_back(new CornerPath('-', 5, 74, cornerPathVector.at(0)));
	objectList.push_back(new CornerPath('-', 6, 74, cornerPathVector.at(0)));
	objectList.push_back(new CornerPath('-', 7, 74, cornerPathVector.at(0)));
	objectList.push_back(new CornerPath('-', 8, 74, cornerPathVector.at(0)));
	objectList.push_back(new CornerPath('-', 9, 74, cornerPathVector.at(0)));
	objectList.push_back(new CornerPath('"', 10, 74, cornerPathVector.at(5)));
	objectList.push_back(new Bush(1, 73, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new CornerPath('[', 2, 73, cornerPathVector.at(2)));
	objectList.push_back(new Path(3, 73, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(4, 73, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(5, 73, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(6, 73, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(7, 73, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(8, 73, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(9, 73, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new CornerPath(']', 10, 73, cornerPathVector.at(3)));
	objectList.push_back(new Bush(11, 73, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(1, 72, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new CornerPath('[', 2, 72, cornerPathVector.at(2)));
	objectList.push_back(new Path(3, 72, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(4, 72, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(5, 72, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(6, 72, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(7, 72, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(8, 72, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new Path(9, 72, pathVector.at(rand() % pathVector.size())));
	objectList.push_back(new CornerPath(']', 10, 72, cornerPathVector.at(3)));
	objectList.push_back(new Bush(11, 72, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new House(-21, 72, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-7, 72, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-11, 63, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-21, 54, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-7, 54, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-11, 45, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-21, 36, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-7, 36, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-11, 27, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-21, 18, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-7, 18, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(-11, 9, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new Bush(1, 0, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new CornerPath(',', 2, 0, cornerPathVector.at(6)));
	objectList.push_back(new CornerPath('~', 3, 0, cornerPathVector.at(1)));
	objectList.push_back(new CornerPath('~', 4, 0, cornerPathVector.at(1)));
	objectList.push_back(new CornerPath('~', 5, 0, cornerPathVector.at(1)));
	objectList.push_back(new CornerPath('~', 6, 0, cornerPathVector.at(1)));
	objectList.push_back(new CornerPath('~', 7, 0, cornerPathVector.at(1)));
	objectList.push_back(new CornerPath('~', 8, 0, cornerPathVector.at(1)));
	objectList.push_back(new CornerPath('~', 9, 0, cornerPathVector.at(1)));
	objectList.push_back(new CornerPath('.', 10, 0, cornerPathVector.at(7)));
	objectList.push_back(new House(-7, 0, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new Bush(11, 0, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(1, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(2, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(3, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(4, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(5, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(6, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(7, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(8, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(9, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new Bush(10, -1, bushVector.at(rand() % bushVector.size())));
	objectList.push_back(new House(-9, -8, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(2, -8, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(12, -8, housesVector.at(rand() % housesVector.size())));
	objectList.push_back(new House(21, -8, housesVector.at(rand() % housesVector.size())));
	for (MapObject*m : objectList) {
		m->init();
	}

	for (Item *i : itemList) {
		i->init();
	}

}

Map::Map(){}


Map::~Map(){}
