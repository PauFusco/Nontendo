#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	nat = KOREA;
	if (nat == KOREA) {
		// idle with disc animation
		idlediscAnim.PushBack({ 4, 7, 52, 36 });
		idlediscAnim.PushBack({ 58, 7, 52, 36 });
		idlediscAnim.speed = 0.05f;

		// idle animation
		idleAnim.PushBack({ 379, 7, 42, 38 });
		idleAnim.speed = 0.1f;

		// Move up
		upAnim.PushBack({ 146, 49, 27, 44 });
		upAnim.PushBack({ 179, 49, 27, 44 });
		upAnim.PushBack({ 214, 49, 26, 50 });
		upAnim.PushBack({ 247, 49, 24, 44 });
		upAnim.PushBack({ 276, 49, 26, 44 });
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

		// Disc throw
		normalthrowAnim.PushBack({ 110, 6, 34, 38 });
		normalthrowAnim.PushBack({ 144, 6, 42, 35 });
		normalthrowAnim.PushBack({ 191, 3, 47, 46 });
		normalthrowAnim.PushBack({ 240, 4, 37, 42 });
		normalthrowAnim.speed = 0.5f;

		// Smack anim
		smackAnim.PushBack({  });
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

	currentAnimation = &idlediscAnim;

	NthrowFx = App->audio->LoadFx("Assets/Sound/1 NORMAL THROW.wav");
	explosionFx = App->audio->LoadFx("Assets/Sound/explosion.wav");

	position.x = 20;
	position.y = 100;

	// TODO 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 27, 33 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	if (!hasDisc && !animationLocked) {
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
			collider->SetPos(position.x, position.y);
			if (App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_REPEAT)
			{
				dashDir = LEFT;
				animationLocked = true;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
			collider->SetPos(position.x, position.y);
			if (App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_REPEAT)
			{
				dashDir = RIGHT;
				animationLocked = true;
				collider->SetPos(position.x + 34, position.y);
			}

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
			if (App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_REPEAT)
			{
				dashDir = DOWN;
				animationLocked = true;
				collider->SetPos(position.x, position.y + 34);
			}

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
			if (App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_REPEAT)
			{
				dashDir = UP;
				animationLocked = true;
			}
		}

		if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			&& App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_REPEAT)
		{
			dashDir = RIGHT;
			animationLocked = true;
			collider->SetPos(position.x + 34, position.y);

		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			// currentAnimation = &smackAnim;
			// animationLocked = true;
		}
	}

	int sx = 3, sy;

	if (hasDisc) {
		//currentAnimation = &idlediscAnim;
	}

	if (hasDisc && App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		sy = -2;
		currentAnimation = &normalthrowAnim;
		App->particles->AddParticle(App->particles->disc, position.x + 35, position.y, sx, sy, Collider::Type::DISC);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}

	if (hasDisc && App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN
		&& App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		sy = 2;
		currentAnimation = &normalthrowAnim;
		App->particles->AddParticle(App->particles->disc, position.x + 35, position.y, sx, sy, Collider::Type::DISC);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);
	}

	if (hasDisc
		&& App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		sx = 5;
		sy = 0;
		currentAnimation = &normalthrowAnim;
		App->particles->AddParticle(App->particles->disc,
			position.x + 30, position.y, sx, sy, Collider::Type::DISC);
		hasDisc = false;
		App->audio->PlayFx(NthrowFx);

	}

	if (animationLocked) {
		switch (dashDir) {
		case RIGHT:
			currentAnimation = &rightdashAnim;
			position.x += 3 * speed;
			collider->SetPos(position.x + 34, position.y);
			break;

		case LEFT:
			currentAnimation = &leftdashAnim;
			position.x -= 4 * speed;
			collider->SetPos(position.x, position.y);
			break;

		case DOWN:
			currentAnimation = &downdashAnim;
			position.y += 4 * speed;
			collider->SetPos(position.x, position.y + 34);
			break;

		case UP:
			currentAnimation = &updashAnim;
			position.y -= 4 * speed;
			collider->SetPos(position.x, position.y + 4);
			break;
		}

		dashingFC--;
		if (dashingFC == 0) {
			dashingFC = animFC;
			animationLocked = false;
		}
	}
	// If no up/down/right/left movement detected, set the current animation back to idle
	else if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		&& !hasDisc)
	{
		currentAnimation = &idleAnim;

		collider->SetPos(position.x + 7, position.y);
	}
	currentAnimation->Update();


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL) {
		if (position.y >= 150) position.y = 150;
		if (position.y <= 47) position.y = 47;
	}
	if (c2->type == Collider::Type::RED) {
		if (position.x >= 117) position.x = 117;
	}
	if (c2->type == Collider::Type::GOAL) {
		if (position.x >= -15) position.x = 0;
	}
}