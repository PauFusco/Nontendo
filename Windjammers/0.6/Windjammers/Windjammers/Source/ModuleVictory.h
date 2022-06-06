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
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp() override;
public:

	// The win spritesheet
	SDL_Texture* victoryTexture;

	// Victory state
	bool win_player = false;
	bool win_enemy = false;

	// Win-Lose asset activated
	bool win_lose = false;

	// Position of the counter in the map
	iPoint counterPosition;

	int win = 0;
	int winFont = -1;
	char winner[10] = { "\0" };
};

#endif
