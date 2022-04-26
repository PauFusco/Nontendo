#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleDisc.h"
#include "Collider.h"

#include "../External_Libraries/SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	nat = KOREA;
	if (nat == KOREA) {
		// idle animation
		idleAnim.PushBack({ 6, 7, 52, 36 });
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
		downAnim.PushBack({ 45, 57, 27, 33 });
		downAnim.PushBack({ 79, 52, 30, 43 });
		downAnim.PushBack({ 114, 56, 27, 35 });
		downAnim.speed = 0.1f;

		// Move right
		rightAnim.PushBack({ 426,  7, 26, 36 });
		rightAnim.PushBack({ 457,  7, 34, 35 });
		rightAnim.PushBack({ 6, 55, 32, 36 });
		rightAnim.speed = 0.1f;

		// Move left
		leftAnim.PushBack({ 76, 161, 32, 37 });
		leftAnim.PushBack({ 39, 161, 36, 38 });
		leftAnim.PushBack({ 3, 161, 37, 37 });
		leftAnim.speed = 0.1f;
	}
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	if (nat == KOREA) texture = App->textures->Load("Assets/Korea movements.png"); // Korea sprites
	
	if (nat == ITALY) texture = App->textures->Load("Assets/Italy movements.png"); // Italy sprites

	if (nat == USA) texture = App->textures->Load("Assets/USA movements.png"); // USA sprites
	
	currentAnimation = &idleAnim;

	NthrowFx = App->audio->LoadFx("Assets/Sound/1 NORMAL THROW.wav");
	explosionFx = App->audio->LoadFx("Assets/Sound/explosion.wav");

	position.x = 20;
	position.y = 100;

	// TODO 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 27, 33 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	if (!hasDisc) {
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
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
	}
	
	int sx = 3, sy;
	
	if (hasDisc
		&& App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		sy = -2;
		App->particles->AddParticle(App->particles->disc, position.x + 20, position.y, sx, sy, Collider::Type::PLAYER_SHOT);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}
	
	if (hasDisc
		&& App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN
		&& App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		sy = 2;
		App->particles->AddParticle(App->particles->disc, position.x + 20, position.y, sx, sy, Collider::Type::PLAYER_SHOT);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}
	
	if (hasDisc
		&& App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		sx = 5;
		sy = 0;
		App->particles->AddParticle(App->particles->disc,
			position.x + 20, position.y, sx, sy, Collider::Type::PLAYER_SHOT);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}
	
	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	{
		currentAnimation = &idleAnim;

		// TODO 4: Update collider position to player position
		collider->SetPos(position.x + 7, position.y);
	}
	currentAnimation->Update();

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
	if (c2->type == Collider::Type::WALL) {
		if (position.y >= 150) position.y = 150;
		if (position.y <= 47) position.y = 47;
	}
}