#include "Bone.h"



Bone::Bone(int i, int y, GLuint texture) : Item(i, y, texture) {}

Bone::~Bone(){
	itemTexture = 0;
	width = 0;
	height = 0;
}
