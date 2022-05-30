#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput(bool startEnabled) : Module(startEnabled)
{}

ModuleInput::~ModuleInput()
{}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i) && controllerP1 == nullptr)
		{
			controllerP1 = SDL_GameControllerOpen(i);
		}
		else if (SDL_IsGameController(i) && controllerP2 == nullptr)
		{
			controllerP2 = SDL_GameControllerOpen(i);
			break;
		}

	}
	if (controllerP1 == nullptr && controllerP2 == nullptr)
	{
		LOG("No Controllers found")
	}
	if (controllerP1 != nullptr && controllerP2 == nullptr)
	{
		LOG("One Controller found")
	}
	

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

Update_Status ModuleInput::PreUpdate()
{
	//Read new SDL events, mostly from the window
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return Update_Status::UPDATE_STOP;
	}

	//Read all keyboard data and update our custom array
	SDL_PumpEvents();

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {

	}

	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		LOG("Button press detected");
		switch(event.cbutton.button){
		case(SDL_CONTROLLER_BUTTON_A):
			keys[SDL_SCANCODE_SPACE] = KEY_DOWN;
			break;
		}
	}


	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}