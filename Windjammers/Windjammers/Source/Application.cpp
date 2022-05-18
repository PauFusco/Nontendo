#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"
#include "ModuleEnemy.h"
#include "ModuleVictory.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	
	modules[1] = textures = new ModuleTextures(true);
	modules[2] = audio = new ModuleAudio(true);
	modules[3] = input = new ModuleInput(true);

	modules[4] = scene = new ModuleScene(false);
	modules[5] = player = new ModulePlayer(false);
	modules[6] = enemy = new ModuleEnemy(false);

	modules[7] = particles = new ModuleParticles(true);
	modules[8] = collisions = new ModuleCollisions(true);

	modules[9] = render = new ModuleRender(true);
	modules[10] = fade = new ModuleFadeToBlack(true);
	modules[11] = intro = new SceneIntro(true);
	modules[12] = victory = new ModuleVictory(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	//By now we will consider that all modules are always active
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	SDL_Delay(17);

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->CleanUp();

	return ret;
}
