#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "SceneLevel1.h"


#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	disc.anim.PushBack({  82, 48, 16, 16 });
	disc.anim.PushBack({ 114, 48, 16, 16 });
	disc.anim.PushBack({ 146, 48, 16, 16 });
	disc.anim.PushBack({ 178, 48, 16, 16 });
	disc.lifetime = 85;
	disc.anim.speed = 0.1f;

	discIdlek.anim.PushBack({237,64,5,13});

	discIdleI.anim.PushBack({113,47,18,17});

	discIdleU.anim.PushBack({ 113,47,18,17 });

	discFly.anim.PushBack({ 0, 0, 17, 44 });
	discFly.anim.PushBack({ 18, 0, 25, 44 });
	discFly.anim.PushBack({ 44, 0, 36, 44 });
	discFly.anim.PushBack({ 81, 0, 28, 44 });
	discFly.anim.PushBack({ 110, 0, 21, 44 });
	discFly.anim.PushBack({ 132, 0,  3, 44 });
	discFly.anim.PushBack({ 136, 0, 23, 44 });
	discFly.anim.PushBack({ 160, 0, 33, 44 });
	discFly.anim.PushBack({ 194, 0, 43, 44 });
	discFly.anim.PushBack({ 160, 0, 33, 44 });
	discFly.anim.PushBack({ 136, 0, 23, 44 });
	discFly.anim.PushBack({ 132, 0,  3, 44 });
	discFly.anim.PushBack({ 110, 0, 21, 44 });
	discFly.anim.PushBack({ 81, 0, 28, 44 });
	discFly.anim.PushBack({ 44, 0, 36, 44 });
	discFly.anim.PushBack({ 18, 0, 25, 44 });
	discFly.anim.PushBack({ 0, 0, 17, 44 });
	discFly.anim.speed = 0.2f;
	discFly.anim.loop = false;
	discFly.lifetime = 70;

	fire.anim.PushBack({});
	fire.anim.PushBack({});
	fire.anim.PushBack({});
	fire.anim.PushBack({});
	fire.anim.PushBack({});
	fire.anim.loop = false;
	fire.lifetime = 10;
	discFly.anim.speed = 0.4f;

	// Menu
	P1ind.anim.PushBack({});
	P1ind.anim.loop = true;

	P2ind.anim.PushBack({});
	P2ind.anim.loop = true;
	
	// Win
	win.anim.PushBack({ 0, 65, 100, 32 });
	win.anim.loop = true;

	// Lose
	lose.anim.PushBack({ 137, 64, 100, 27 });
	lose.anim.loop = true;

	wallrbFx = App->audio->LoadFx("Assets/Music/SFX/8 REBOUND.wav");
	goalFx = App->audio->LoadFx("Assets/Music/SFX/10 POINT.wav");
	recieve = App->audio->LoadFx("Assets/Music/SFX/HIT 1.wav");
	hit = App->audio->LoadFx("Assets/Music/SFX/HIT 3.wav");

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	switch (App->sceneLevel_1->scene) {
	case BEACH:
		DiscTexture = App->textures->Load("Assets/Sprites/SCENES/DiscBeach.png");
		break;
	case LAWN:
		DiscTexture = App->textures->Load("Assets/Sprites/SCENES/DiscLawn.png");
		break;
	case TILED:
		DiscTexture = App->textures->Load("Assets/Sprites/SCENES/DiscTiled.png");
	}

	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	Particle* p = particles[0];
	if (p != nullptr)
	{
		if (c2->type == Collider::Type::WALL)
		{
			App->audio->PlayFx(wallrbFx);
			p->speed.y = -p->speed.y;
		}

		if (c2->type == Collider::Type::GOAL3)
		{
			App->audio->PlayFx(goalFx);
			p->speed.x = 0;
			p->speed.y = 0;
			p->isAlive = false;

			if (p->position.x > 152)
			{
				App->player->score += 3;
				SDL_Delay(20);
				App->enemy->hasDisc = true;
				App->enemy->nextIsSpecial = false;
			}
			else
			{
				App->player->score_e += 3;
				SDL_Delay(20);
				App->player->hasDisc = true;
				App->player->nextIsSpecial = false;
			}
			App->sceneLevel_1->timerStop = true;
			CleanUp();
		}

		if (c2->type == Collider::Type::GOAL5)
		{
			App->audio->PlayFx(goalFx);
			p->speed.x = 0;
			p->speed.y = 0;
			p->isAlive = false;

			if (p->position.x > 152)
			{
				App->player->score += 5;
				SDL_Delay(20);
				App->enemy->hasDisc = true;
				App->enemy->nextIsSpecial = false;
			}
			else
			{
				App->player->score_e += 5;
				SDL_Delay(20);
				App->player->hasDisc = true;
				App->player->nextIsSpecial = false;
			}
			App->sceneLevel_1->timerStop = true;
			CleanUp();
		}

		if (c2->type == Collider::Type::PLAYER)
		{
			if (!App->player->nextIsSpecial)
			{
				App->audio->PlayFx(recieve);
				App->player->hasDisc = true;
				CleanUp();
			}
			else
			{
				App->player->hasDisc = true;
				int x = p->position.x;
				int y = p->position.y;
				App->audio->PlayFx(hit);
				CleanUp();
				AddParticle(discFly, x, y, 0, 0, Collider::NONE);
				
			}
		}
		if (c2->type == Collider::Type::ENEMY)
		{
			if (!App->enemy->nextIsSpecial)
			{
				App->audio->PlayFx(recieve);
				App->enemy->hasDisc = true;
				CleanUp();
			}
			else
			{
				App->enemy->hasDisc = true;
				int x = p->position.x;
				int y = p->position.y;
				App->audio->PlayFx(hit);
				CleanUp();
				AddParticle(discFly, x, y, 0, 0, Collider::NONE);
				
			}
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(DiscTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, int speedx, int speedy, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->position.x = x;
			p->position.y = y;
			p->speed.x = speedx;
			p->speed.y = speedy;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}