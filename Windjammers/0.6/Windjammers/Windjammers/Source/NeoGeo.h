#pragma once
#ifndef __NEO_GEO_H__
#define __NEO_GEO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class NeoGeo : public Module
{
public:
	//Constructor
	NeoGeo(bool startEnabled);

	//Destructor
	~NeoGeo();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp() override;


public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture_white = nullptr;
	SDL_Texture* bgTexture_black = nullptr;
	SDL_Texture* NeoGeoLOGO = nullptr;
	SDL_Texture* MaxLOGO = nullptr;

	Animation NeoGeoA;
	Animation Max;

	Animation* currentAnimation = nullptr;

	int neogeospeed = 1;
	int maxspeed = 1;

};

#endif