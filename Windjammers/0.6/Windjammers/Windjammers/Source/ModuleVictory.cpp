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

	victoryTexture = App->textures->Load("Assets/Sprites/WINdjammers.png");


	return ret;
}

Update_Status ModuleVictory::Update()
{
	if (App->player->score == 12) {
		win_player = true;
	}
	else if (App->player->score_e == 12) {
		win_enemy = true;
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleVictory::PostUpdate()
{
	// Draw everything --------------------------------------
	if (win_player) {
		App->render->Blit(victoryTexture, 150, 100, nullptr, 0.0f);
	}
	else if (win_enemy) {
		App->render->Blit(victoryTexture, 500, 100, nullptr, 0.0f);
	}
	else if ((App->sceneLevel_1->decimas) + (App->sceneLevel_1->unidades) == 0) {
		if (App->player->score >= App->player->score_e) {
			App->render->Blit(victoryTexture, 150, 100, nullptr, 0.0f);
		}
		else {
			App->render->Blit(victoryTexture, 500, 100, nullptr, 0.0f);
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}
