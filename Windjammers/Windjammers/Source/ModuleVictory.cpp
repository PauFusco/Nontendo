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

	victoryTexture = App->textures->Load("Assets/marcadores windjammers.png"); 


	return ret;
}

// 0, 100, 436, 136

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
		App->render->Blit(victoryTexture, 0, 0, NULL);
	}

	return update_status::UPDATE_CONTINUE;
}
