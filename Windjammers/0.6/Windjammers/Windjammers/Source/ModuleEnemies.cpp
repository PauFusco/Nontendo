#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"

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
	switch (nat) {
	case (KOREA):

		texture = App->textures->Load("Assets/Sprites/PLAYERS/Korea movements.png"); // Korea sprites

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
		
		specialAnim.PushBack({ 105, 200, 43, 54 });
		specialAnim.PushBack({ 161, 200, 45, 54 });
		specialAnim.PushBack({ 215, 200, 53, 54 });
		specialAnim.PushBack({ 271, 200, 45, 54 });
		specialAnim.PushBack({ 322, 200, 51, 54 });
		specialAnim.PushBack({ 387, 200, 41, 54 });
		specialAnim.speed = 0.2f;

		specialCharge = App->audio->LoadFx("Assets/Music/CHARACTER SFX/KOREA/VOICES/4 B4 SPECIAL.wav");
		specialThrow = App->audio->LoadFx("Assets/Music/CHARACTER SFX/KOREA/VOICES/7 NORMAL SPECIAL.wav");

		break;

	case ITALY:
		texture = App->textures->Load("Assets/Sprites/PLAYERS/Italy movements.png"); // Italy sprites
		
		// idle animation with disc
		idlediscAnim.PushBack({  });
		idlediscAnim.PushBack({  });
		idlediscAnim.speed = 0.05f;

		// idle animation
		idleAnim.PushBack({  });
		idleAnim.PushBack({  });
		idleAnim.PushBack({  });
		idleAnim.PushBack({  });
		idleAnim.speed = 0.1f;

		// Move up
		upAnim.PushBack({  });
		upAnim.PushBack({  });
		upAnim.PushBack({  });
		upAnim.PushBack({  });
		upAnim.PushBack({  });
		upAnim.PushBack({  });
		upAnim.speed = 0.1f;

		// Move down
		downAnim.PushBack({  });
		downAnim.PushBack({  });
		downAnim.PushBack({  });
		downAnim.PushBack({  });
		downAnim.PushBack({  });
		downAnim.PushBack({  });
		downAnim.PushBack({  });
		downAnim.speed = 0.1f;

		// Move right
		rightAnim.PushBack({  72, 11, 45, 45 });
		rightAnim.PushBack({ 156, 11, 37, 45 });
		rightAnim.PushBack({ 193, 11, 32, 45 });
		rightAnim.PushBack({ 225, 11, 47, 45 });
		rightAnim.speed = 0.1f;

		// Move left
		leftAnim.PushBack({ 419, 169, 45, 45 });
		leftAnim.PushBack({ 343, 169, 37, 45 });
		leftAnim.PushBack({ 311, 169, 32, 45 });
		leftAnim.PushBack({ 264, 169, 47, 45 });
		leftAnim.speed = 0.1f;

		// Dash right
		rightdashAnim.PushBack({  55, 238, 79, 38 });

		// Dash left
		leftdashAnim.PushBack ({ 242, 123, 80, 35 });

		// Dash up
		updashAnim.PushBack   ({ 142, 216, 35, 80 });

		// Dash down
		downdashAnim.PushBack ({  12, 216, 35, 80 });

		specialAnim.PushBack({ 281, 208, 46, 43 });
		specialAnim.PushBack({ 334, 208, 44, 43 });
		specialAnim.PushBack({ 388, 208, 45, 46 });
		specialAnim.PushBack({ 440, 208, 45, 43 });
		specialAnim.PushBack({ 282, 251, 45, 48 });
		specialAnim.PushBack({ 334, 251, 45, 44 });
		specialAnim.speed = 0.2f;

		specialCharge = App->audio->LoadFx("Assets/Music/CHARACTER SFX/ITALY/VOICES/4 B4 SPECIAL.wav");
		specialThrow = App->audio->LoadFx("Assets/Music/CHARACTER SFX/ITALY/VOICES/9 VERTICAL SPECIAL.wav");

		break;

	case USA:
		texture = App->textures->Load("Assets/Sprites/PLAYERS/USA movements.png"); // USA spriteS

		// idle animation with disc
		idlediscAnim.PushBack({14,396,41,47  });
		idlediscAnim.PushBack({  });
		idlediscAnim.speed = 0.05f;

		// idle animation
		idleAnim.PushBack({ 14,396,41,47 });
		idleAnim.PushBack({71,396,41,47  });
		idleAnim.PushBack({116,396,41,47  });
		idleAnim.PushBack({164,396,41,47  });
		idleAnim.PushBack({  });
		idleAnim.PushBack({  });
		idleAnim.speed = 0.1f;

		// Move up
		upAnim.PushBack({12,335,42,55  });
		upAnim.PushBack({54,335,42,55  });
		upAnim.PushBack({94,335,42,55  });
		upAnim.speed = 0.1f;

		// Move down
		downAnim.PushBack({323,276,43,49  });
		downAnim.PushBack({226,276,43,49  });
		downAnim.PushBack({370,276,43,49  });
		downAnim.speed = 0.1f;

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

		specialAnim.PushBack({ 151, 339, 48, 52 });
		specialAnim.PushBack({ 214, 339, 46, 52 });
		specialAnim.PushBack({ 274, 339, 48, 52 });
		specialAnim.PushBack({ 335, 339, 46, 52 });
		specialAnim.PushBack({ 393, 339, 48, 52 });
		specialAnim.PushBack({ 451, 339, 46, 52 });
		specialAnim.speed = 0.2f;

		specialCharge = App->audio->LoadFx("Assets/Music/CHARACTER SFX/USA/VOICES/4 B4 SPECIAL.wav");
		specialThrow = App->audio->LoadFx("Assets/Music/CHARACTER SFX/USA/VOICES/7 NORMAL SPECIAL.wav");

		break;
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
				App->audio->PlayFx(dashFx);
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
				App->audio->PlayFx(dashFx);
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
				App->audio->PlayFx(dashFx);
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
			collider->SetPos(position.x + 30, position.y);
			App->audio->PlayFx(dashFx);

		}

		if (App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
		{
			nextIsSpecial = true;
			canDash = false;
		}
	}

	if (nextIsSpecial && hasDisc) {
		animationLocked = true;
		specialFC--;
		if (currentAnimation != &specialAnim)
		{
			specialAnim.Reset();
			currentAnimation = &specialAnim;
			App->audio->PlayFx(specialCharge);
		}
		if (specialFC == 0) {
			App->particles->CleanUp();
			App->audio->PlayFx(specialThrow);

			int sx = -5;
			int sy = 20;
			App->particles->AddParticle(App->particles->disc, position.x - 30, position.y, sx, sy, Collider::Type::DISC);

			nextIsSpecial = false;
			animationLocked = false;
			hasDisc = false;

			specialFC = 70;
		}
	}

	int sx = -3, sy;

	if (hasDisc) {
		currentAnimation = &idlediscAnim;
	}

	if (hasDisc && App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
		{
			sy = -2;
			/*currentAnimation = &normalthrowAnim;

			animFC--;
			if (animFC == 0) {
				animFC = 10;
				animationLocked = false;
			}*/

			if (!animationLocked)
			{
				App->particles->AddParticle(App->particles->disc, position.x + 35, position.y, sx, sy, Collider::Type::DISC);
				hasDisc = false;
				App->audio->PlayFx(NthrowFx);
				canDash = true;
			}
		}

		else if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			sy = 2;
			App->particles->AddParticle(App->particles->disc, position.x - 20, position.y, sx, sy, Collider::Type::DISC);
			hasDisc = false;
			App->audio->PlayFx(NthrowFx);
		}

		else
		{
			sx = -5;
			sy = 0;
			App->particles->AddParticle(App->particles->disc, position.x - 20, position.y, sx, sy, Collider::Type::DISC);
			hasDisc = false;
			App->audio->PlayFx(NthrowFx);
			canDash = true;
		}
	}
	
	if (animationLocked && canDash) {
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
		if (position.x >= 251) position.x = 266;
	}
}