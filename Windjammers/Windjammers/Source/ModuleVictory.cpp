#include "ModuleVictory.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"

ModuleVictory::ModuleVictory(bool startEnabled) : Module(startEnabled)
{
}

ModuleVictory::~ModuleVictory()
{

}

// Load assets
bool ModuleVictory::Start()
{


	LOG("Loading background assets");

	bool ret = true;

	victoryTexture = App->textures->Load("Assets/WINdjammers.png"); 


	return ret;
}

update_status ModuleVictory::Update()
{
	if (App->player->points == 6 || App->enemy->points == 6) {
		win = true;
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleVictory::PostUpdate()
{
	// Draw everything --------------------------------------
	if (win) {
		App->render->Blit(victoryTexture, 150, 100, nullptr, 0.0f);
	}
	return update_status::UPDATE_CONTINUE;
}
