#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Particles.png");


	explosion.anim.PushBack({ 451, 12, 60, 53 });
	explosion.anim.PushBack({ 451, 12, 60, 53 });
	explosion.anim.PushBack({ 451, 12, 60, 53 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.1f;
	explosion.lifetime = 5;

	disc.anim.PushBack({ 117, 560, 16, 16 });
	disc.anim.PushBack({ 149, 560, 16, 16 });
	disc.anim.PushBack({ 181, 560, 16, 16 });
	disc.anim.PushBack({ 213, 560, 16, 16 });

	disc.lifetime = 85;
	disc.anim.speed = 0.1f;

	wallrbFx = App->audio->LoadFx("Assets/Sound/8 REBOUND.wav");
	goalFx = App->audio->LoadFx("Assets/Sound/10 POINT.wav");

	// Counter spritesheet
	counterTexture = App->textures->Load("Assets/markador wj chikito.png");

	//Counter animation
	counter.anim.PushBack({ 2, 21, 14, 12 }); // 0 points
	counter.anim.PushBack({ 2, 21, 14, 12 }); // 0 points
	/*
	counterTexture1.PushBack({ 15, 21, 14, 12 }); // 1 points
	counterTexture1.PushBack({ 32, 22, 14, 12 }); // 2 points
	counterTexture1.PushBack({ 48, 22, 14, 12 }); // 3 points
	counterTexture1.PushBack({ 66, 21, 14, 12 }); // 5 points
	counterTexture1.PushBack({ 2, 35, 14, 12 }); // 6 points
	counterTexture1.PushBack({ 32, 35, 14, 12 }); // 8 points
	counterTexture1.PushBack({ 48, 35, 14, 12 }); // 9 points
	*/
	counter.anim.loop = true;

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
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		Particle* p = particles[i];
		if (p != nullptr)
		{
			if (c2->type == Collider::Type::WALL)
			{
				p->speed.y = -p->speed.y;
				App->audio->PlayFx(wallrbFx);
				App->particles->AddParticle(explosion, p->position.x, p->position.y, 0, 0);
			}

			if (c2->type == Collider::Type::GOAL)
			{
				if (p->position.x > 152) {
					App->player->player1points += 5;
				}
				else {
					// +5 to the second playerd
				}
				// p->speed.x = -p->speed.x
				App->audio->PlayFx(goalFx);
				p->speed.x = 0;
				p->speed.y = 0;
				p->isAlive = false;
				App->player->hasDisc = true;
				CleanUp();
			}
			if (c2->type == Collider::Type::PLAYER)
			{
				p->position.x = App->player->position.x + 50;
				p->position.y = App->player->position.y + 15;
				p->speed.x = 0;
				p->speed.y = 0;
				CleanUp();
				App->player->hasDisc = true;
			}
		}
	}
}

update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}
	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, int speedx, int speedy, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			//p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
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
