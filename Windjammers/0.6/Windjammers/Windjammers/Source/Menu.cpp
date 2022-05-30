#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

#include "Menu.h"

Menu::Menu(bool startEnabled) : Module(startEnabled)
{

}

Menu::~Menu()
{

}

// Load assets
bool Menu::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	p1np2 = App->textures->Load("Assets/Sprites/mas sprites.png");

	p1.PushBack({618,175,640,193});

	



	bgTexture = App->textures->Load("Assets/Sprites/menu de pj.png");
	App->audio->PlayMusic("Assets/Music/MENU/TUTORIAL MUSIC.ogg", 1.0f);

	KoreaSelect = App->audio->LoadFx("Assets/Music/CHARACTER SFX/KOREA/VOICES/1 SELECTED.wav");
	ItalySelect = App->audio->LoadFx("Assets/Music/CHARACTER SFX/ITALY/VOICES/1 SELECTED.wav");
	USASelect = App->audio->LoadFx("Assets/Music/CHARACTER SFX/USA/VOICES/1 SELECTED.wav");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	int p1x = 10;
	int p2x = 10;
	int y = 50;

	P1.selector = App->particles->P1ind;
	App->particles->AddParticle(P1.selector, p1x, y, 0, P1.speed);

	P2.selector = App->particles->P2ind;
	App->particles->AddParticle(P2.selector, p2x, y, 0, P2.speed);

	return ret;
}

Update_Status Menu::Update()
{
	// Player 2 Character selection
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN && !P2.Locked && P2.character < 3)
	{
		P2.selector.position.y += P2.speed;
		P2.character++;

	}
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN && !P2.Locked && P2.character >= 0)
	{
		P2.selector.position.y -= P2.speed;
		P2.character--;

	}
	if (App->input->keys[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN)
	{
		P2.Locked = true;
		switch (P2.character) {
		case(0):
			P2.FinalSelection = KOREA;
			App->audio->PlayFx(KoreaSelect);
			break;
		case(1):
			P2.FinalSelection = ITALY;
			App->audio->PlayFx(ItalySelect);
			break;
		case(2):
			P2.FinalSelection = USA;
			App->audio->PlayFx(USASelect);
			break;
		}
	}
	
	// Player 1 Character selection
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && !P2.Locked && P2.character >= 0)
	{
		P1.selector.position.y -= P1.speed;
		P1.character--;

	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN && !P2.Locked && P2.character < 3)
	{
		P1.selector.position.y += P1.speed;
		P1.character++;

	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		P1.Locked = true;
		switch (P1.character) {
		case(0):
			P1.FinalSelection = KOREA;
			App->audio->PlayFx(KoreaSelect);
			break;
		case(1):
			P1.FinalSelection = ITALY;
			App->audio->PlayFx(ItalySelect);
			break;
		case(2):
			P1.FinalSelection = USA;
			App->audio->PlayFx(USASelect);
			break;
		}
	}

	if (P1.Locked && P2.Locked)
	{		
		App->player->nat = P1.FinalSelection;
		App->enemy->nat = P2.FinalSelection;

		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 50);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status Menu::PostUpdate()
{
	// Draw everything
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(p1np2, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool Menu::CleanUp()
{
	App->particles->CleanUp();
	return true;
}