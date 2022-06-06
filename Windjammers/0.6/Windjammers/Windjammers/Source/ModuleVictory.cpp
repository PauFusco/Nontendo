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
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"

#include <stdio.h>

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

	return ret;
}

Update_Status ModuleVictory::Update()
{
	if (App->player->score >= 12) {
		win_player = true;
	}
	else if (App->player->score_e >= 12) {
		win_enemy = true;
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleVictory::PostUpdate()
{
	// Draw everything --------------------------------------
	if (win_player) {
		win_lose = true;
	}
	else if (win_enemy) {
		win_lose = true;
	}
	else if ((App->sceneLevel_1->decimas) + (App->sceneLevel_1->unidades) == 0) {
		if (!App->player->score >= App->player->score_e)	win_lose = true;
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleVictory::CleanUp()
{
	return true;
}