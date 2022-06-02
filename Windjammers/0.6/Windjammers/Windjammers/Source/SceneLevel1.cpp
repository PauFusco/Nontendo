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

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	switch (scene) {
	case BEACH:
		bgTexture = App->textures->Load("Assets/Sprites/SCENES/BEACH.png");
		App->audio->PlayMusic("Assets/Music/STAGES/BEACH.ogg");
		break;
	
	case LAWN:
		bgTexture = App->textures->Load("Assets/Sprites/SCENES/LAWN.png");
		App->audio->PlayMusic("Assets/Music/STAGES/LAWN.ogg");
		break;

	case TILED:
		bgTexture = App->textures->Load("Assets/Sprites/SCENES/TILED.png");
		App->audio->PlayMusic("Assets/Music/STAGES/TILED.ogg");
		break;
	}
	// Colliders ---
	App->collisions->AddCollider({   0, 224, 3930, 16 }, Collider::Type::WALL);

	App->collisions->AddCollider({   0,  32, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({   0, 182, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 144,  56,  15, 130 }, Collider::Type::RED );
	App->collisions->AddCollider({   0,  56,   8, 132 }, Collider::Type::GOAL);
	App->collisions->AddCollider({ 296,  56,   8, 132 }, Collider::Type::GOAL);

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemy->Enable();
	App->particles->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	if (App->input->keys[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->menu, 40);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemy->Disable();
	App->particles->CleanUp();

	return true;
}