#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "../External_Libraries/SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	// idle animation
	idleAnim.PushBack({  6, 7, 52, 36 });
	idleAnim.PushBack({ 58, 8, 52, 36 });
	idleAnim.speed = 0.05f;

	// Move up
	upAnim.PushBack({ 146, 54, 27, 39 });
	upAnim.PushBack({ 179, 54, 27, 39 });
	upAnim.PushBack({ 214, 48, 26, 50 });
	upAnim.PushBack({ 247, 54, 24, 39 });
	upAnim.PushBack({ 276, 54, 26, 39 });
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({  45, 57, 27, 33 });
	downAnim.PushBack({  79, 52, 30, 43 });
	downAnim.PushBack({ 114, 56, 27, 35 });
	downAnim.speed = 0.1f;

	// Move right
	rightAnim.PushBack({ 426,  7, 26, 36 });
	rightAnim.PushBack({ 457,  7, 34, 35 });
	rightAnim.PushBack({   6, 55, 32, 36 });
	upAnim.speed = 0.1f;

	// Move left
	leftAnim.PushBack({  });
	leftAnim.PushBack({  });
	leftAnim.PushBack({  });
	leftAnim.PushBack({  });
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Korea movements.png"); // arcade version
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 25;
	position.y = 100;

	// TODO 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 27, 33 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
		collider->SetPos(position.x + 7, position.y);
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
		collider->SetPos(position.x + 7, position.y);
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
		collider->SetPos(position.x, position.y);
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
		collider->SetPos(position.x, position.y);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {
		currentAnimation = &idleAnim;

		// TODO 4: Update collider position to player position
		collider->SetPos(position.x + 7, position.y);
	}
	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Detect collision with a wall. If so, go back to intro screen.
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
}