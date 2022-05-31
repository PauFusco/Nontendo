#pragma once
#ifndef __PANTALLA_DE_CARGA_H__
#define __PANTALLA_DE_CARGA_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class PantallaDeCarga : public Module
{
public:
	//Constructor
	PantallaDeCarga(bool startEnabled);

	//Destructor
	~PantallaDeCarga();

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
	
	

	Animation* currentAnimation = nullptr;

	Animation PlayerKorea;
	Animation PlayerItalia;
	Animation PlayerUsa;
	Animation EnemyKorea;
	Animation EnemyItalia;
	Animation EnemyUsa;
	Animation pantalla1;
	Animation pantalla2;

	float Timer = 0.0f; 
	int visualicacion = -5;
	int movimiento = 1; 

};

#endif
