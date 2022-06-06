#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleVictory.h"

#include <stdio.h>

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{
	
}

// Load assets
bool SceneLevel1::Start()
{
	App->victory->win_lose, App->victory->win_enemy, App->victory->win_player = false;

	LOG("Loading background assets");

	bool ret = true;
	switch (scene) {
	case BEACH:
		bgTexture = App->textures->Load("Assets/Sprites/SCENES/BEACH.png");
		App->audio->PlayMusic("Assets/Music/STAGES/BEACH.ogg");
		
		App->collisions->AddCollider({   8,  55, 10, 49 }, Collider::Type::GOAL3);
		App->collisions->AddCollider({   8, 105, 10, 47 }, Collider::Type::GOAL5);
		App->collisions->AddCollider({   8, 152, 10, 49 }, Collider::Type::GOAL3);
		
		App->collisions->AddCollider({ 285,  56, 10, 49 }, Collider::Type::GOAL3);
		App->collisions->AddCollider({ 285, 105, 10, 47 }, Collider::Type::GOAL5);
		App->collisions->AddCollider({ 285, 152, 10, 49 }, Collider::Type::GOAL3);
		
		App->collisions->AddCollider({   0,  35, 304,  21 }, Collider::Type::WALL);
		App->collisions->AddCollider({   0, 185, 304,  19 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 146,  56,  11, 129 }, Collider::Type::RED);

		break;
	
	case LAWN:
		bgTexture = App->textures->Load("Assets/Sprites/SCENES/LAWN.png");
		App->audio->PlayMusic("Assets/Music/STAGES/LAWN.ogg");
		
		App->collisions->AddCollider({  16,  45, 20, 59 }, Collider::Type::GOAL3);
		App->collisions->AddCollider({  16, 104, 10, 48 }, Collider::Type::GOAL5);
		App->collisions->AddCollider({  16, 152, 20, 59 }, Collider::Type::GOAL3);

		App->collisions->AddCollider({ 268,  56, 20, 59 }, Collider::Type::GOAL3);
		App->collisions->AddCollider({ 268, 104, 20, 48 }, Collider::Type::GOAL5);
		App->collisions->AddCollider({ 268, 152, 20, 59 }, Collider::Type::GOAL3);

		App->collisions->AddCollider({   0,  22, 304,  22 }, Collider::Type::WALL);
		App->collisions->AddCollider({   0, 199, 304,  18 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 145,  44,  15, 155 }, Collider::Type::RED);

		break;

	case TILED:
		bgTexture = App->textures->Load("Assets/Sprites/SCENES/TILED.png");
		App->audio->PlayMusic("Assets/Music/STAGES/TILED.ogg");
		
		App->collisions->AddCollider({ 17,  56, 8, 32 }, Collider::Type::GOAL5);
		App->collisions->AddCollider({ 17,  88, 8, 77 }, Collider::Type::GOAL3);
		App->collisions->AddCollider({ 17, 165, 8, 32 }, Collider::Type::GOAL5);

		App->collisions->AddCollider({ 279,  56, 8, 32 }, Collider::Type::GOAL3);
		App->collisions->AddCollider({ 279,  88, 8, 77 }, Collider::Type::GOAL5);
		App->collisions->AddCollider({ 279, 165, 8, 32 }, Collider::Type::GOAL3);

		App->collisions->AddCollider({   0,  38, 304,  19 }, Collider::Type::WALL);
		App->collisions->AddCollider({   0, 185, 304,  19 }, Collider::Type::WALL);
		App->collisions->AddCollider({ 146,  56,  13, 129 }, Collider::Type::RED);

		break;
	}

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemy->Enable();
	App->particles->Enable();

	char lookupTable[] = { "0123456789" };
	timeFont = App->fonts->Load("Assets/Fonts/timer  wj.png", lookupTable, 1);

	return ret;
}

Update_Status SceneLevel1::Update()
{
	if (App->victory->win_player)
	{
		App->particles->AddParticle(App->particles->win, 37, 58, 0, 0, Collider::NONE);
		App->particles->AddParticle(App->particles->lose, 182, 58, 0, 0, Collider::NONE);
		App->fade->FadeToBlack(this, (Module*)App->mapmenu, 100);
		timeWinLose--;
		if (timeWinLose == 0) {
			App->sceneLevel_1->CleanUp();
			App->victory->win_lose, App->victory->win_enemy, App->victory->win_player = false;
		}
	}
	else if (App->victory->win_enemy)
	{
		App->particles->AddParticle(App->particles->win, 182, 58, 0, 0, Collider::NONE);
		App->particles->AddParticle(App->particles->lose, 37, 58, 0, 0, Collider::NONE);
		App->fade->FadeToBlack(this, (Module*)App->mapmenu, 100);
		timeWinLose--;
		if (timeWinLose == 0) {
			App->sceneLevel_1->CleanUp();
			App->victory->win_lose, App->victory->win_enemy, App->victory->win_player = false;
		}
	}

	

	if (!timerStop && !(decimas + unidades == 0)) {
		if (reloj == 0) {
			if (unidades == 0) {
				decimas -= 1;
				unidades = 9;
			}
			else {
				unidades -= 1;
			}
			reloj = 60;
		}
		else {
			reloj -= 1;
		}
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->victory->win_player = true;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	// Draw UI (score) --------------------------------------
	sprintf_s(timer, 10, "%d", decimas);
	App->fonts->BlitText(144, 21, timeFont, timer);

	sprintf_s(timer, 10, "%d", unidades);
	App->fonts->BlitText(152, 21, timeFont, timer);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->player->score = 0;
	App->player->score_e = 0;
	unidades = 0;
	decimas = 3;
	reloj = 60;
	timeWinLose = 180;
	timerStop = true;
	App->enemy->Disable();
	App->collisions->CleanUp();
	App->particles->CleanUp();

	return true;
}