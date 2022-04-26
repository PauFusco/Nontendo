#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
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
	texture = App->textures->Load("Assets/Particles.png");

	// Explosion particle
	/*explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	*/

	explosion.anim.PushBack({ 451, 12, 60, 53 });
	explosion.anim.PushBack({ 451, 12, 60, 53 });
	explosion.anim.PushBack({ 451, 12, 60, 53 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.1f;
	//explosion.lifetime = 10;

	disc.anim.PushBack({ 117, 560, 16, 16 });
	disc.anim.PushBack({ 149, 560, 16, 16 });
	disc.anim.PushBack({ 181, 560, 16, 16 });
	disc.anim.PushBack({ 213, 560, 16, 16 });

	disc.lifetime = 85;
	disc.anim.speed = 0.1f;

	return true;
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
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		Particle* p = particles[i];
		if (p != nullptr)
		{
			if (c2->type == Collider::Type::GOAL)
			{
				// p->speed.x = -p->speed.x;
				// p->position.x = App->player->position.x + 50;
				// p->position.y = App->player->position.y + 15;
				
				p->speed.x = 0;
				p->speed.y = 0;
				if (p->lifetime > 0) {
					App->player->hasDisc = true;
				}
			}

			if (c2->type == Collider::Type::WALL)
			{
				p->speed.y = -p->speed.y;
				App->particles->AddParticle(explosion, p->position.x, p->position.y, 0, 0);

			}

			if (c2->type == Collider::Type::PLAYER)
			{
				p->position.x = App->player->position.x + 50;
				p->position.y = App->player->position.y + 15;
				p->speed.x = 0;
				p->speed.y = 0;
				
				delete p->collider;
				delete p;
				
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