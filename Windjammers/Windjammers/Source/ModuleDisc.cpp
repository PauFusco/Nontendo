#include "ModuleDisc.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "../External_Libraries/SDL/include/SDL_scancode.h"


ModuleDisc::ModuleDisc()
{
	// While disc is static on the hand
	idleAnim.PushBack({ 117, 48, 16, 16 });
	idleAnim.PushBack({ 117, 48, 16, 16 });
	idleAnim.speed = 0.05f;

	// While disc is flying
	slowAnim.PushBack({ 117, 48, 16, 16 });
	slowAnim.PushBack({ 149, 48, 16, 16 });
	slowAnim.PushBack({ 181, 48, 16, 16 });
	slowAnim.PushBack({ 213, 48, 16, 16 });
	slowAnim.speed = 0.05f;
}

ModuleDisc::~ModuleDisc()
{

}

bool ModuleDisc::Start()
{
	LOG("Loading disc textures");

	bool ret = true;

	position.x = 100;
	position.y = 220;

	texture = App->textures->Load("Assets/DiscBeach.png"); 

	// Disc collider
	collider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::DISC, this);

	return ret;
}

update_status ModuleDisc::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		currentAnimation = &slowAnim;
		// App->audio->PlayFx(laserFx);
	}
	currentAnimation->Update();

	/*
	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}
	*/

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDisc::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleDisc::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Detect collision with a wall. If so, go back to intro screen.
	if (c1 == collider && destroyed == false)
	{
		/*
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);
		*/

		// App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
}