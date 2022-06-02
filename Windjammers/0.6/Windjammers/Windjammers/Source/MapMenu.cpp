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

	bgTexture = App->textures->Load("Assets/Sprites/MENUS/Beach Selected.png");

	selected = App->audio->LoadFx("Assets/Music/MENU/START SELECT.wav");

	int x = 10;
	int y = 10;
	
	selection.Locked = false;

	return true;
}

Update_Status MapMenu::Update()
{
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && selection.scenario > 0)
	{
		selection.scenario--;
		switch (selection.scenario) {
		case 0:
			bgTexture = App->textures->Load("Assets/Sprites/MENUS/Beach Selected.png");
			break;
		case 1:
			bgTexture = App->textures->Load("Assets/Sprites/MENUS/Lawn Selected.png");
			break;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN && selection.scenario < 2)
	{
		selection.scenario++;
		switch (selection.scenario) {
		case 1:
			bgTexture = App->textures->Load("Assets/Sprites/MENUS/Lawn Selected.png");
			break;
		case 2:
			bgTexture = App->textures->Load("Assets/Sprites/MENUS/Tiled Selected.png");
			break;
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && !selection.Locked)
	{
		selection.Locked = true;
		switch (selection.scenario) {
		case 0:
			selection.FinalSelection = BEACH;
			break;
		case 1:
			selection.FinalSelection = LAWN;
			break;
		case 2:
			selection.FinalSelection = TILED;
			break;
		}
		App->audio->PlayFx(selected);
	}

	if(selection.Locked)
	{
		App->sceneLevel_1->scene = selection.FinalSelection;
		App->fade->FadeToBlack(this, (Module*)App->pantalladecarga, 50);
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status MapMenu::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool MapMenu::CleanUp()
{
	App->particles->CleanUp();
	return true;
}