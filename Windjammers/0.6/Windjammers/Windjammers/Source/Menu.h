#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class Menu : public Module
{
public:
	//Constructor
	Menu(bool startEnabled);

	//Destructor
	~Menu();

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
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* p1np2 = nullptr; 
	iPoint position;

	Animation* currentAnimation = nullptr;

	struct characterSelected {
		bool Locked = false;
		int character = 0;
		int speed = 55;
		int x1 = 89; 
		int y1 = 64;
		int x2 = 59;
		int y2 = 64; 
		Particle selector;
		Nation FinalSelection;
	};

	int speed = 1; 

	uint KoreaSelect = 0;
	uint ItalySelect = 1;
	uint USASelect = 2;
	
	characterSelected P1;
	characterSelected P2;

	Animation p1; 
	Animation p2; 
};

#endif
