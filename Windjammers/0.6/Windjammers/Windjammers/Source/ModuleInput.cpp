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
	
	SDL_GameControllerAddMapping("030000006f0e00008401000000000000,Faceoff Premiere Wired Pro Controller for Nintendo Switch,platform:Windows,a:b1,b:b2,x:b0,y:b3,back:b8,guide:b12,start:b9,leftstick:b10,rightstick:b11,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a2,righty:a3,lefttrigger:b6,righttrigger:b7,");
	
	SDL_Init(SDL_INIT_EVERYTHING);

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i))
		{
			controllerP1 = SDL_GameControllerOpen(i);
			LOG("A controller was found");
			break;
		}
	}
	if (controllerP1 == nullptr)
	{
		LOG("No Controllers found")
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

	SDL_PumpEvents();

	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}
	SDL_GameControllerUpdate();
	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		LOG("Button press detected");
		switch (event.cbutton.button) {
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			keys[SDL_SCANCODE_A] = KEY_DOWN;
			break;
		
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			keys[SDL_SCANCODE_D] = KEY_DOWN;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			keys[SDL_SCANCODE_W] = KEY_DOWN;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			keys[SDL_SCANCODE_S] = KEY_DOWN;
			break;

		case SDL_CONTROLLER_BUTTON_B:
			keys[SDL_SCANCODE_SPACE] = KEY_DOWN;
			break;

		case SDL_CONTROLLER_BUTTON_A:
			keys[SDL_SCANCODE_X] = KEY_DOWN;
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