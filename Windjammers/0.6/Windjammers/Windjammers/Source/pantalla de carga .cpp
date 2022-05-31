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
	PlayerKorea.PushBack({1385,230,47,32});
	PlayerItalia.PushBack({1381,264,47,32});
	PlayerUsa.PushBack({ 1374,192,47,32 });
	EnemyKorea.PushBack({1432,231,47,32});
	EnemyItalia.PushBack({1429,263,47,32});
	EnemyUsa.PushBack({1424,192,47,32});
	pantalla1.PushBack({713,361,304,223});
	pantalla2.PushBack({1090,361,304,223});

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
	

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 50);

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status PantallaDeCarga::PostUpdate()
{
	SDL_Rect rect = PlayerKorea.GetCurrentFrame();
	SDL_Rect rect2 = PlayerItalia.GetCurrentFrame();
	SDL_Rect rect3 = PlayerUsa.GetCurrentFrame();
	SDL_Rect rect4 = EnemyKorea.GetCurrentFrame();
	SDL_Rect rect5 = PlayerItalia.GetCurrentFrame();
	SDL_Rect rect6 = PlayerUsa.GetCurrentFrame();
	SDL_Rect rect7 = pantalla1.GetCurrentFrame();
	SDL_Rect rect8 = pantalla2.GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &rect7);
	

	return Update_Status::UPDATE_CONTINUE;
}

bool PantallaDeCarga::CleanUp()
{
	return true;
}