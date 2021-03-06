#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//Constructor
	SceneIntro(bool startEnabled);

	//Destructor
	~SceneIntro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	void UpdateShipPosition();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	Animation* currentAnimation = nullptr;

	int speed = 1;

	Animation palmeras;
	Animation titulo;
	Animation disco; 
	Animation subtitulo;

	float shipMovementTimer = 0.0f;

	
	int shipPosition_x = -5;

	
	int shipMovement_x = 1;

	int shipPosition_y = -5;


	int shipMovement_y = 1;
};




#endif