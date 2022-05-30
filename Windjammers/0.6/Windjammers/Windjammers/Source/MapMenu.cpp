#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

#include "MapMenu.h"

MapMenu::MapMenu(bool startEnabled) : Module(startEnabled)
{

}

MapMenu::~MapMenu()
{

}

bool MapMenu::Start()
{
	LOG("Loading assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/fonfo mapas.png");

	selected = App->audio->LoadFx("Assets/Music/MENU/START SELECT.wav");

	int x = 10;
	int y = 10;

	return true;
}

Update_Status MapMenu::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status MapMenu::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool MapMenu::CleanUp()
{
	return true;
}