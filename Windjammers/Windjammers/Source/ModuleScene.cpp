#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Beach Stadium.png");
	App->audio->PlayMusic("Assets/Sound/BEACH.ogg");

	// Colliders ---
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	// TODO 2: Add colliders for the first columns of the level
	App->collisions->AddCollider({   0,  32, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({   0, 182, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 144,  56,  15, 130 }, Collider::Type::RED);
	App->collisions->AddCollider({   0,  56,   8, 132 }, Collider::Type::GOAL);
	App->collisions->AddCollider({ 296,  56,   8, 132 }, Collider::Type::GOAL);
	
	return ret;
}

update_status ModuleScene::Update()
{
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}