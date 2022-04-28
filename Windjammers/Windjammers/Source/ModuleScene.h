#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene();

	//Destructor
	~ModuleScene();

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

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;

	// The counter spritesheet
	SDL_Texture* counterTexture = nullptr;

	// It will be switched depending on the counter's state direction
	Animation* currentAnimation = nullptr;

	// Counter animations
	Animation counterTexture1;
	Animation counterTexture2;

	// Counter states
	int counterState1 = 0;
	int counterState2 = 0;

	// Position of the counter in the map
	iPoint counterPosition;
};

#endif

