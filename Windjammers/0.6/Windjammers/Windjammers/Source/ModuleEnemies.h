#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__

#include "Module.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

#define MAX_ENEMIES 100

class ModuleEnemy : public Module
{
public:
	// Constructor
	ModuleEnemy(bool startEnabled);

	// Destructor
	~ModuleEnemy();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:

	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// Idle animations
	Animation idlediscAnim;
	Animation idleAnim;

	// Movement animations
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;

	// Dash animations
	Animation rightdashAnim;
	Animation leftdashAnim;
	Animation updashAnim;
	Animation downdashAnim;

	// Action animations
	Animation normalthrowAnim;

	// Smack animation
	Animation specialAnim;

	// Stores the nation
	Nation nat;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// SFX
	uint NthrowFx = 0;
	uint explosionFx = 0;
	uint dashFx = 0;
	uint specialCharge = 0;
	uint specialThrow = 0;

	// Disc indent
	bool hasDisc = false;

	bool nextIsSpecial = false;
	int specialFC = 70;

	// Enum of different dash directions
	enum dashingDir {
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

	dashingDir dashDir;

	bool animationLocked = false;

	int animFC = 10;

	bool canDash = true;

	unsigned int dashingFC = animFC;

	// Points
	int points = 0;
};

#endif //!__MODULE_PLAYER_H__
