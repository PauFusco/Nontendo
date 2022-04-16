#ifndef __MODULE_DISC_H__
#define __MODULE_DISC_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleDisc : public Module
{
public:
	// Constructor
	ModuleDisc();

	// Destructor
	~ModuleDisc();

	// Called when the module is activated
	// Loads the necessary textures for the disc
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles disc movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the disc sprite
	update_status PostUpdate() override;

	// Collision callback, called when the disc intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the disc in the map
	iPoint position;

	// The speed in which we move the disc (pixels per frame)
	int speed = 1;

	// The disc spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	

	// The pointer to the current player animation
	// It will be switched depending on the disc's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation slowAnim;

	// The disc's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	// uint destroyedCountdown = 120;

	// Sound effects indices

};

#endif //!__MODULE_DISC_H__
