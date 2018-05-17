#include "Menu.h"

/****************************Texture loading method used throughout******************************************/
GLuint loadPNG(char* name)
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

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::init(int screenHeight, int screenWidth) {
	PlaySound("audio/Carefree.wav", NULL, SND_ASYNC);
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	menu1 = loadPNG("textures/menus/menu1.png");
	menu2 = loadPNG("textures/menus/menu2.png");
	howToPlay = loadPNG("textures/menus/howToPlay.png");
	winSingle = loadPNG("textures/menus/winSingle.png");
	lossHealth = loadPNG("textures/menus/noLife.png");
	//menu1 = loadPNG("textures/menus/menu.png");
}

void Menu::display(int screenHeight, int screenWidth) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	if (outcomeCard == 0) {
		if (menuCard == 1) {
			glBindTexture(GL_TEXTURE_2D, menu1);
		}
		else if (menuCard == 2) {
			glBindTexture(GL_TEXTURE_2D, menu2);
		}
		else if (menuCard == 3) {
			glBindTexture(GL_TEXTURE_2D, howToPlay);
		}
	}
	else if (outcomeCard == 1) {
		menuCard = 4;
		glBindTexture(GL_TEXTURE_2D, winSingle);
	}
	else if (outcomeCard == 2) {
		menuCard = 4;
		glBindTexture(GL_TEXTURE_2D, lossHealth);
	}
	//else if(outcomeCard == 1) {
	//	glBindTexture(GL_TEXTURE_2D, winSingle);
	//}
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-screenWidth / 4, 0);
		glTexCoord2f(0.0, 1.0); glVertex2f(-screenWidth / 4, screenHeight / 2);
		glTexCoord2f(1.0, 1.0); glVertex2f(screenWidth / 4, screenHeight / 2);
		glTexCoord2f(1.0, 0.0); glVertex2f(screenWidth / 4, 0);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Menu::update(int mouseX, int mouseY, bool leftClick) {
	//std::cout << "mouseX : " << mouseX << "     mouseY : " << mouseY << std::endl;
	if (menuCard == 1) {
		if ((mouseX > 140 && mouseX < 365) && (mouseY > 195 && mouseY < 280) && leftClick) {
			menuCard++;
		}
		else if ((mouseX > 445 && mouseX < 670) && (mouseY > 195 && mouseY < 280) && leftClick) {
			quit=true;
		}
	}
	else if (menuCard == 2) {
		if (mouseX > 408 && mouseX < 1172) {
			if ((mouseY > 710 && mouseY < 830) && leftClick) {
				menuCard++;
			}
			else if ((mouseY > 490 && mouseY < 610) && leftClick) {
				singlePlayerActivated = true;
			}
			else if ((mouseY > 280 && mouseY < 405) && leftClick) {
				singlePlayerActivated = true;
				twoPlayerActivated = true;
			}
			else if ((mouseY > 70 && mouseY < 190) && leftClick) {
				menuCard--;
			}
		}
	}
	else if (menuCard == 3) {
		if ((mouseX > 1100 && mouseX < 1485) && (mouseY > 30 && mouseY < 90) && leftClick) {
				menuCard=1;
		}
	}
	else if (outcomeCard == 1) {
		if ((mouseX > 1335 && mouseX < 1585) && (mouseY > 25 && mouseY < 80) && leftClick) {
			outcomeCard = 0;
			menuCard = 1;
		}
	}
	else if (outcomeCard == 2) {
		if ((mouseX > 1315 && mouseX < 1565) && (mouseY > 30 && mouseY < 85) && leftClick) {
			outcomeCard = 0;
			menuCard = 1;
		}
	}

}