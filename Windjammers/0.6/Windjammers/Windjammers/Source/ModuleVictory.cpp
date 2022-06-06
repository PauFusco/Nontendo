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

	// victoryTexture = App->textures->Load("Assets/Sprites/WINdjammers.png");

	winFont = App->fonts->Load("Assets/Sprites/WINdjammers.png", "1", 1);


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
		sprintf_s(winner, 10, "%d", win);
		App->fonts->BlitText(150, 300, winFont, winner);
		// App->render->Blit(victoryTexture, 150, 100, nullptr, 0.0f);
		win_lose = true;
	}
	else if (win_enemy) {
		App->render->Blit(victoryTexture, 500, 100, nullptr, 0.0f);
		win_lose = true;
	}
	else if ((App->sceneLevel_1->decimas) + (App->sceneLevel_1->unidades) == 0) {
		if (App->player->score >= App->player->score_e) {
			App->render->Blit(victoryTexture, 150, 100, nullptr, 0.0f);
		}
		else {
			App->render->Blit(victoryTexture, 500, 100, nullptr, 0.0f);
		}
		win_lose = true;
	}
	

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleVictory::CleanUp()
{
	return true;
}