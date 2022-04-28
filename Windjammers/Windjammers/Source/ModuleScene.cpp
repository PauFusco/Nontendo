#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

ModuleScene::ModuleScene(bool startDisabled) : Module(startDisabled)
{
	//Counter animation
	counterTexture1.PushBack({ 2, 21, 14, 12 }); // 0 points
	counterTexture1.PushBack({ 2, 21, 14, 12 }); // 0 points
	
	counterTexture1.PushBack({ 15, 21, 14, 12 }); // 1 points
	counterTexture1.PushBack({ 32, 22, 14, 12 }); // 2 points
	counterTexture1.PushBack({ 48, 22, 14, 12 }); // 3 points
	counterTexture1.PushBack({ 66, 21, 14, 12 }); // 5 points
	counterTexture1.PushBack({ 2, 35, 14, 12 }); // 6 points
	counterTexture1.PushBack({ 32, 35, 14, 12 }); // 8 points
	counterTexture1.PushBack({ 48, 35, 14, 12 }); // 9 points
	
	counterTexture1.speed = 1.0f;
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/introwinsjammers.png");

	// Counter spritesheet
	counterTexture = App->textures->Load("Assets/markadores wj chikitos.png");
	currentAnimation = &counterTexture1;

	App->audio->PlayMusic("Assets/Sound/BEACH.ogg");

	// Colliders ---
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	// TODO 2: Add colliders for the first columns of the level
	App->collisions->AddCollider({ 0,  32, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 182, 304,  15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 144,  56,  15, 130 }, Collider::Type::RED);
	App->collisions->AddCollider({ 0,  56,   8, 132 }, Collider::Type::GOAL);
	App->collisions->AddCollider({ 296,  56,   8, 132 }, Collider::Type::GOAL);

	// Counter
	/*
	if (Collider::Type::GOAL == Collider::Type::DISC) {
		counterState1++;
	}
	else if (counterState >= 0)
	{
		switch (counterState) {
		case 0:
			counterTexture.PushBack({ 0,0,0,0 });
			counterTexture.PushBack({ 0,0,0,0 });
			break;
		case 10:
			counterTexture.PushBack({ 0,0,0,0 });
			counterTexture.PushBack({ 0,0,0,0 });
			break;
		};
	};
	*/
	counterPosition.x = 112;
	counterPosition.y = 16;

	return ret;
}

update_status ModuleScene::Update()
{
	// Counter updates
	currentAnimation = &counterTexture1;
	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(counterTexture, counterPosition.x, counterPosition.y, &rect);
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp() {
	App->collisions->CleanUp();

	return true;
}