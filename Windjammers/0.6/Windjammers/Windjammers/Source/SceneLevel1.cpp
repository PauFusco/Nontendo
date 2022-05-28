#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

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

	bgTexture = App->textures->Load("Assets/Sprites/Beach Stadium.png");
	App->audio->PlayMusic("Assets/Music/STAGES/BEACH.ogg");

	// Colliders ---
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	App->collisions->AddCollider({   0,  32, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({   0, 182, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 144,  56,  15, 130 }, Collider::Type::RED);
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

	return true;
}