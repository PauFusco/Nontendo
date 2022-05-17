#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Enum of different possible nations
	enum Nation {
		KOREA,
		ITALY,
		USA
	};
	
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// Players score points
	int player1points = 0;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation rightdashAnim;
	Animation leftdashAnim;
	Animation updashAnim;
	Animation downdashAnim;


	// Stores the nation
	Nation nat;
	
	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// SFX
	uint NthrowFx = 0;
	uint explosionFx = 0;

	// Disc indent
	bool hasDisc = true;

	// Enum of different dash directions
	enum dashingDir {
		RIGHT,
		LEFT,
		UP,
		DOWN,
		A,
		MAX
	};
	dashingDir dashDir = A;
	
	bool animationLocked = false;

	int animFC = 10;

	unsigned int dashingFC = animFC;

	// Points
	int points = 0;

};

#endif //!__MODULE_PLAYER_H__