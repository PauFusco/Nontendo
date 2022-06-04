#include "pantalla de carga.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

PantallaDeCarga::PantallaDeCarga(bool startEnabled) : Module(startEnabled)
{
	PlayerKorea.PushBack ({743,797,127,81});
	PlayerItalia.PushBack({720,619,127,81 });
	PlayerUsa.PushBack   ({743, 708,127,81 });
	
	EnemyKorea.PushBack ({877,708,127,81 });
	EnemyItalia.PushBack({877, 797,127,81 });
	EnemyUsa.PushBack   ({897, 619,127,81 });

	pantalla.PushBack({713,361,304,223});
	pantalla.PushBack({1090,361,304,223});
	pantalla.speed = 0.8f;
}

PantallaDeCarga::~PantallaDeCarga()
{

}

// Load assets
bool PantallaDeCarga::Start()
{
	LOG("Loading background assets");
	
	bool ret = true;

	App->audio->PlayMusic("Assets/Music/MENU/Loading Screen.wav", 1.0f);

	bgTexture = App->textures->Load("Assets/Sprites/mas sprites.png");
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status PantallaDeCarga::Update()
{
	framecounter--;
	if (framecounter == 0) {
		App->audio->PlayMusic("");
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 40);
		framecounter = 130;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status PantallaDeCarga::PostUpdate()
{
	SDL_Rect rect1 = PlayerKorea.GetCurrentFrame();
	SDL_Rect rect2 = PlayerItalia.GetCurrentFrame();
	SDL_Rect rect3 = PlayerUsa.GetCurrentFrame();
	SDL_Rect rect4 = EnemyKorea.GetCurrentFrame();
	SDL_Rect rect5 = EnemyItalia.GetCurrentFrame();
	SDL_Rect rect6 = EnemyUsa.GetCurrentFrame();
	SDL_Rect rect7 = pantalla.GetCurrentFrame();
	

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &rect7);
	
	switch (App->player->nat)
	{
	case KOREA:
		App->render->Blit(bgTexture, 21, 52, &rect1);
		break;

	case ITALY:
		App->render->Blit(bgTexture, 21, 52, &rect2);
		break;

	case USA:
		App->render->Blit(bgTexture, 21, 52, &rect3);
		break;
	}

	switch (App->enemy->nat)
	{
	case KOREA:
		App->render->Blit(bgTexture, 155, 52, &rect4);
		break;

	case ITALY:
		App->render->Blit(bgTexture, 155, 52, &rect5);
		break;

	case USA:
		App->render->Blit(bgTexture, 155, 52, &rect6);
		break;

	}

	return Update_Status::UPDATE_CONTINUE;
}

bool PantallaDeCarga::CleanUp()
{
	return true;
}