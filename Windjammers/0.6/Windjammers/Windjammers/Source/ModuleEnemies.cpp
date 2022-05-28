#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_scancode.h"
#include "ModuleInput.h"


ModuleEnemy::ModuleEnemy(bool startEnabled) : Module(startEnabled)
{
	
}

ModuleEnemy::~ModuleEnemy()
{

}

bool ModuleEnemy::Start()
{
	LOG("Loading enemy textures");

	bool ret = true;
	if (nat == KOREA)
	{
		texture = App->textures->Load("Assets/Sprites/Korea movements.png"); // Korea sprites
		
		// idle animation with disc
		idlediscAnim.PushBack({ 124, 161, 52, 36 });
		idlediscAnim.PushBack({ 178, 161, 52, 36 });
		idlediscAnim.speed = 0.05f;

		// idle animation
		idleAnim.PushBack({ 379, 7, 42, 38 });
		idleAnim.speed = 0.1f;

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

		// Dash right
		rightdashAnim.PushBack({ 310, 56, 68, 33 });

		// Dash left
		leftdashAnim.PushBack({ 310, 98, 68, 33 });

		// Dash up
		updashAnim.PushBack({ 308, 135, 33, 68 });

		// Dash down
		downdashAnim.PushBack({ 340, 135, 33, 68 });
	}

	if (nat == ITALY)
	{
		texture = App->textures->Load("Assets/Sprites/Italy movements.png"); // Italy sprites
	}
	
	if (nat == USA)
	{
		texture = App->textures->Load("Assets/Sprites/USA movements.png"); // USA sprites
	}

	currentAnimation = &idlediscAnim;

	NthrowFx = App->audio->LoadFx("Assets/Music/SFX/1 NORMAL THROW.wav");
	explosionFx = App->audio->LoadFx("Assets/Music/explosion.wav");

	position.x = 240;
	position.y = 100;

	// TODO 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x + 10, position.y, 27, 33 }, Collider::Type::ENEMY, this);

	return ret;
	//return true;
}

Update_Status ModuleEnemy::Update()
{
	if (!hasDisc && !animationLocked) {
		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
			collider->SetPos(position.x, position.y);
			if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_REPEAT)
			{
				dashDir = LEFT;
				animationLocked = true;
			}
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
			collider->SetPos(position.x, position.y);
			if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_REPEAT)
			{
				dashDir = RIGHT;
				animationLocked = true;
				collider->SetPos(position.x + 34, position.y);
			}
		}

		if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
			collider->SetPos(position.x, position.y);
			if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_REPEAT)
			{
				dashDir = DOWN;
				animationLocked = true;
				collider->SetPos(position.x, position.y + 34);
			}

		}

		if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
			collider->SetPos(position.x, position.y);
			if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_REPEAT) {
				dashDir = UP;
				animationLocked = true;
			}
		}

		if ((App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE)
			&& App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_REPEAT)
		{
			dashDir = LEFT;
			animationLocked = true;
			collider->SetPos(position.x + 34, position.y);

		}

		if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN)
		{
			// currentAnimation = &smackAnim;
			// animationLocked = true;
		}
	
	}
	int sx = -3, sy;

	if (hasDisc) {
		currentAnimation = &idlediscAnim;
	}

	if (hasDisc
		&& App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN
		&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		sy = -2;
		App->particles->AddParticle(App->particles->disc, position.x - 20, position.y, sx, sy, Collider::Type::DISC);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}

	if (hasDisc
		&& App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN
		&& App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		sy = 2;
		App->particles->AddParticle(App->particles->disc, position.x - 20, position.y, sx, sy, Collider::Type::DISC);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}

	if (hasDisc
		&& App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		sx = -5;
		sy = 0;
		App->particles->AddParticle(App->particles->disc, position.x - 20, position.y, sx, sy, Collider::Type::DISC);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}

	if (animationLocked) {
		switch (dashDir) {
		case RIGHT:
			currentAnimation = &rightdashAnim;
			position.x += 4 * speed;
			break;

		case LEFT:
			currentAnimation = &leftdashAnim;
			position.x -= 4 * speed;
			break;

		case DOWN:
			currentAnimation = &downdashAnim;
			position.y += 4 * speed;
			break;

		case UP:
			currentAnimation = &updashAnim;
			position.y -= 4 * speed;
			break;
		}

		dashingFC--;
		if (dashingFC == 0) {
			dashingFC = animFC;
			animationLocked = false;
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	else if ((App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE) && !hasDisc)
	{
		currentAnimation = &idleAnim;

		collider->SetPos(position.x + 17, position.y);
	}
	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemy::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}


void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL) {
		if (position.y >= 150) position.y = 150;
		if (position.y <= 47) position.y = 47;
	}
	if (c2->type == Collider::Type::RED) {
		if (position.x <= 145) position.x = 145;
	}
	if (c2->type == Collider::Type::GOAL) {
		if (position.x >= 266) position.x = 266;
	}
}