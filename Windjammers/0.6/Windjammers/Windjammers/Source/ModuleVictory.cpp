#include "ModuleVictory.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "SceneLevel1.h"

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

Update_Status ModuleVictory::Update()
{
	if (App->player->score == 12 || App->player->score_e == 12 || (App->sceneLevel_1->decimas)*10 + (App->sceneLevel_1->unidades) == 0) {
		win = true;
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleVictory::PostUpdate()
{
	// Draw everything --------------------------------------
	if (win) {
		App->render->Blit(victoryTexture, 150, 100, nullptr, 0.0f);
	}
	return Update_Status::UPDATE_CONTINUE;
}
