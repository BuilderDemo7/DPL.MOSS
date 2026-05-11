#pragma once
#include "Vector4.h"

struct PI_MATERIAL_HANDLE {
	int handle_m;
};

struct Sprite {
	Vector4 colour;
	float positionX;
	float positionY;
	float sizeX;
	float sizeY;
	float topLeftU;
	float topLeftV;
	float bottomRightU;
	float bottomRightV;
};

struct SSpriteInstance {
	unsigned int numSprites;
	PI_MATERIAL_HANDLE materialID;
	Sprite *sprites;
	int whichSubstance;
};
