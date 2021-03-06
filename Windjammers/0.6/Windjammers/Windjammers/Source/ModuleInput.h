#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"


#define MAX_KEYS 256

enum KEY_STATE
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	// Constructor
	ModuleInput(bool startEnabled);

	// Destructor
	~ModuleInput();

	// Called on application start.
	// Initializes the SDL system for input detection
	bool Init() override;

	// Called at the beginning of the application loop
	// Updates all input data received from SDL
	Update_Status PreUpdate() override;

	// Called on application exit.
	// Uninitializes the SDL system for input detection
	bool CleanUp() override;

public:
	// An array to fill in the state of all the keyboard keys
	KEY_STATE keys[MAX_KEYS] = { KEY_IDLE };

	struct controller {
		KEY_STATE buttons[SDL_CONTROLLER_BUTTON_MAX];
	};
	
	SDL_GameController* sdl_P1 = nullptr;
	SDL_GameController* sdl_P2 = nullptr;
	controller P1;
	controller P2;
};

#endif // __ModuleInput_H__