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
#include "SceneLevel1.h"


#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading enemy textures");

	bool ret = true;
	switch (nat) {
	case (KOREA):
	
		texture = App->textures->Load("Assets/Sprites/PLAYERS/Korea movements.png"); // Korea sprites

		// idle animation with disc
		idlediscAnim.PushBack({  4, 7, 52, 36});
		idlediscAnim.PushBack({ 58, 7, 52, 36});
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
		downAnim.PushBack({  45, 57, 27, 33 });
		downAnim.PushBack({  79, 52, 30, 43 });
		downAnim.PushBack({ 114, 56, 27, 35 });
		downAnim.speed = 0.1f;

		// Move right
		rightAnim.PushBack({ 426,  7, 26, 36 });
		rightAnim.PushBack({ 457,  7, 34, 35 });
		rightAnim.PushBack({   6, 55, 32, 36 });
		rightAnim.speed = 0.1f;

		// Move left
		leftAnim.PushBack({ 76, 161, 32, 37 });
		leftAnim.PushBack({ 39, 161, 36, 38 });
		leftAnim.PushBack({  3, 161, 37, 37 });
		leftAnim.speed = 0.1f;

		// Dash right
		rightdashAnim.PushBack({ 310, 56, 68, 33 });

		// Dash left
		leftdashAnim.PushBack({ 310, 98, 68, 33 });

		// Dash up
		updashAnim.PushBack({ 308, 135, 33, 68 });

		// Dash down
		downdashAnim.PushBack({ 340, 135, 33, 68 });

		normalthrowAnim.PushBack({ 110, 3, 34, 46 });
		normalthrowAnim.PushBack({ 144, 3, 42, 46 });
		normalthrowAnim.PushBack({ 192, 3, 43, 46 });
		normalthrowAnim.PushBack({ 241, 3, 35, 46 });
		normalthrowAnim.loop = false;
		normalthrowAnim.speed = 0.1f;
		break;
	
	case ITALY:
		texture = App->textures->Load("Assets/Sprites/PLAYERS/Italy movements.png"); // Italy sprites
		
		// idle animation with disc
		idlediscAnim.PushBack({  8, 5, 31, 46 });
		idlediscAnim.PushBack({ 39, 5, 31, 46 });
		idlediscAnim.speed = 0.05f;

		// idle animation
		idleAnim.PushBack({  98, 164, 35, 47 });
		idleAnim.PushBack({ 137, 164, 38, 47 });
		idleAnim.PushBack({ 179, 164, 35, 47 });
		idleAnim.PushBack({ 218, 164, 31, 47 });
		idleAnim.speed = 0.1f;

		// Move up
		upAnim.PushBack({ 187, 52, 45, 56 });
		upAnim.PushBack({ 232, 52, 34, 56 });
		upAnim.PushBack({ 271, 52, 45, 56 });
		upAnim.PushBack({ 316, 52, 34, 56 });
		upAnim.PushBack({ 271, 52, 45, 56 });
		upAnim.PushBack({ 232, 52, 34, 56 });
		upAnim.speed = 0.1f;

		// Move down
		downAnim.PushBack({	365,  5, 40, 46 });
		downAnim.PushBack({ 408,  5, 42, 46 });
		downAnim.PushBack({ 453,  5, 42, 46 });
		downAnim.PushBack({   4, 57, 40, 46 });
		downAnim.PushBack({  49, 57, 42, 46 });
		downAnim.PushBack({  96, 57, 42, 46 });
		downAnim.PushBack({ 408,  5, 42, 46 });
		downAnim.speed = 0.1f;

		// Move right
		rightAnim.PushBack({ 154, 5, 37, 45 });
		rightAnim.PushBack({ 191, 5, 32, 45 });
		rightAnim.PushBack({ 223, 5, 47, 45 });		
		rightAnim.PushBack({ 270, 5, 47, 45 });
		rightAnim.PushBack({ 320, 5, 45, 45 });
		rightAnim.speed = 0.1f;

		// Move left
		leftAnim.PushBack({ 417, 163, 45, 45 });
		leftAnim.PushBack({ 341, 163, 37, 45 });
		leftAnim.PushBack({ 309, 163, 32, 45 });
		leftAnim.PushBack({ 262, 163, 47, 45 });
		leftAnim.speed = 0.1f;

		// Dash right
		rightdashAnim.PushBack({ 240, 117, 80, 35 });

		// Dash left
		leftdashAnim.PushBack ({  55, 238, 79, 37 });

		// Dash up
		updashAnim.PushBack   ({ 142, 216, 35, 80 });

		// Dash down
		downdashAnim.PushBack ({  12, 216, 35, 80 });

		break;

	case USA:
		texture = App->textures->Load("Assets/Sprites/PLAYERS/USA movements.png"); // USA spriteS
		
		// idle animation with disc
		idlediscAnim.PushBack({ 367, 61, 33, 42 });
		idlediscAnim.PushBack({ 419, 61, 34, 42 });
		idlediscAnim.speed = 0.05f;

		// idle animation
		idleAnim.PushBack({  12, 13, 32, 41 });
		idleAnim.PushBack({  62, 13, 33, 41 });
		idleAnim.PushBack({ 113, 13, 33, 41 });
		idleAnim.PushBack({ 164, 13, 32, 41 });
		idleAnim.PushBack({ 208, 13, 32, 41 });
		idleAnim.PushBack({ 245, 13, 32, 41 });
		idleAnim.speed = 0.1f;

		// Move up
		upAnim.PushBack({ 234, 114, 31, 47 });
		upAnim.PushBack({ 239, 225, 34, 40 });
		upAnim.PushBack({ 207, 225, 29, 48 });
		upAnim.speed = 0.1f;

		// Move down
		downAnim.PushBack({ 462,  59, 41, 46 });
		downAnim.PushBack({   5, 116, 39, 43 });
		downAnim.PushBack({  59, 116, 35, 43 });
		downAnim.PushBack({ 109, 116, 35, 43 });
		downAnim.PushBack({ 153, 116, 35, 43 });
		downAnim.speed = 0.07f;

		// Move right
		rightAnim.PushBack({ 272, 117, 38, 41 });
		rightAnim.PushBack({ 329, 117, 28, 41 });
		rightAnim.PushBack({ 374, 117, 35, 41 });
		rightAnim.PushBack({ 424, 117, 38, 41 });
		rightAnim.PushBack({ 374, 117, 35, 41 });
		rightAnim.PushBack({ 329, 117, 28, 41 });
		rightAnim.speed = 0.1f;

		// Move left
		leftAnim.PushBack({ 451, 227, 38, 41 });
		leftAnim.PushBack({ 404, 227, 28, 41 });
		leftAnim.PushBack({ 352, 227, 35, 41 });
		leftAnim.PushBack({ 299, 227, 38, 41 });
		leftAnim.PushBack({ 352, 227, 35, 41 });
		leftAnim.PushBack({ 404, 227, 28, 41 });
		leftAnim.speed = 0.1f;

		// Dash right
		rightdashAnim.PushBack({ 105, 227, 55, 34 });

		// Dash left
		leftdashAnim.PushBack ({ 103, 273, 55, 34 });

		// Dash up
		updashAnim.PushBack   ({  54, 269, 34, 55 });

		// Dash down
		downdashAnim.PushBack ({ 168, 269, 34, 55 });

		break;
	}
	currentAnimation = &idlediscAnim;

	NthrowFx = App->audio->LoadFx("Assets/Music/SFX/1 NORMAL THROW.wav");
	explosionFx = App->audio->LoadFx("Assets/Music/explosion.wav");
	dashFx = App->audio->LoadFx("Assets/Music/SFX/9 SLIDE.wav");

	position.x = 20;
	position.y = 100;

	// TODO 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 27, 33 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//&scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "01235689" };
	scoreFont = App->fonts->Load("Assets/Fonts/counter  wj.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	if (!hasDisc && !animationLocked) {
		canDash = false;
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
				App->audio->PlayFx(dashFx);
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
				App->audio->PlayFx(dashFx);
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
				App->audio->PlayFx(dashFx);
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
				App->audio->PlayFx(dashFx);
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
			App->audio->PlayFx(dashFx);
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			nextIsSpecial = true;
			canDash = false;
			App->sceneLevel_1->timerStop = false;
		}
	}

	if (nextIsSpecial && hasDisc) {
		animationLocked = true;
		specialFC--;
		if (specialFC == 0) {
			App->particles->CleanUp();
			int sx = 5;
			int sy = sx*sx;
			App->particles->AddParticle(App->particles->disc, position.x + 30, position.y, sx, sy, Collider::Type::DISC);
			nextIsSpecial = false;
			animationLocked = false;
			hasDisc = false;
			specialFC = 60;
		}
	}

	int sx = 3, sy;

	if (hasDisc) {
		currentAnimation = &idlediscAnim;
	}

	if (hasDisc && App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			sy = -2;
			currentAnimation = &normalthrowAnim;

			animFC--;
			if (animFC == 0) {
				animFC = 10;
				animationLocked = false;
			}

			if (!animationLocked)
			{
				App->particles->AddParticle(App->particles->disc, position.x + 35, position.y, sx, sy, Collider::Type::DISC);
				hasDisc = false;
				App->audio->PlayFx(NthrowFx);
				canDash = true;
			}
		}

		else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			sy = 2;
			currentAnimation = &normalthrowAnim;

			animFC--;
			if (animFC == 0) {
				animFC = 10;
				animationLocked = false;
			}

			if (!animationLocked)
			{
				App->particles->AddParticle(App->particles->disc, position.x + 35, position.y, sx, sy, Collider::Type::DISC);
				hasDisc = false;
				App->audio->PlayFx(NthrowFx);
				canDash = true;
			}
		}

		else
		{
			sx = 5;
			sy = 0;
			currentAnimation = &normalthrowAnim;

			animFC--;
			if (animFC == 0) {
				animFC = 10;
				animationLocked = false;
			}

			if (!animationLocked)
			{
				App->particles->AddParticle(App->particles->disc, position.x + 30, position.y, sx, sy, Collider::Type::DISC);
				hasDisc = false;
				App->audio->PlayFx(NthrowFx);
				
			}
		}
	}

	if (animationLocked && canDash) {
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

	// Player Score
	if (score < 10) {
		sprintf_s(counter, 10, "%d", score);
		App->fonts->BlitText(111, 16, scoreFont, "0");
		App->fonts->BlitText(127, 16, scoreFont, counter);
	}
	else {
		sprintf_s(counter, 10, "%d", score);
		App->fonts->BlitText(111, 16, scoreFont, counter);
	}

	// Enemy Score
	if (score_e < 10) {
		sprintf_s(counter, 10, "%d", score_e);
		App->fonts->BlitText(159, 16, scoreFont, "0");
		App->fonts->BlitText(175, 16, scoreFont, counter);
	}
	else {
		sprintf_s(counter, 10, "%d", score_e);
		App->fonts->BlitText(159, 16, scoreFont, counter);
	}
	

	// App->fonts->BlitText(120, 100, scoreFont, "this is just a font test");

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

bool ModulePlayer::CleanUp()
{
	return true;
}