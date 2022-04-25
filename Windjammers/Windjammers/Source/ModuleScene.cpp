#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

ModuleScene::ModuleScene()
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
	App->audio->PlayMusic("Assets/BEACH.ogg", 1.0f);

	// Colliders ---
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	// TODO 2: Add colliders for the first columns of the level
	App->collisions->AddCollider({   0,  32, 304,  24 }, Collider::Type::WALL);
	App->collisions->AddCollider({   0, 182, 304,  22 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 144,  56,  15, 130 }, Collider::Type::RED);

	return ret;
}

update_status ModuleScene::Update()
{
	//App->render->camera.x += 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}