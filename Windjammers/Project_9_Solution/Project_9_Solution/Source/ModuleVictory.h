#ifndef __MODULE_VICTORY_H__
#define __MODULE_VICTORY_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleVictory : public Module
{
public:
	//Constructor
	ModuleVictory(bool startEnabled);

	//Destructor
	~ModuleVictory();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:

	// The win spritesheet
	SDL_Texture* victoryTexture;

	// Victory state
	bool win = false;

	// Position of the counter in the map
	iPoint counterPosition;
};

#endif
