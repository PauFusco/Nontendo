#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"



SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	palmeras.PushBack({135,634,304,223});
	titulo.PushBack({297,50,288,129});
	subtitulo.PushBack({319,27,260,13});
	disco.PushBack({41,162,45,28});
	disco.speed = 1.0f;
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	
	

	bgTexture = App->textures->Load("Assets/Sprites/mas sprites.png");

	
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	

	return ret;
}

Update_Status SceneIntro::Update()
{
	disco.Update();

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->menu, 50);
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

void SceneIntro::UpdateShipPosition()
{
	shipMovementTimer++;
	if (shipMovementTimer > 50)
	{
		shipPosition_x += shipMovement_x;
		shipPosition_y += shipMovement_y;

		if (shipPosition_x == 50) shipMovement_x = -1;
		if (shipPosition_x == 20) shipMovement_x = 1;

		if (shipPosition_y == 50) shipMovement_y = -1;
		if (shipPosition_y == 20) shipMovement_y = 1;


		shipMovementTimer = 0;
	}

}
// Update: draw background
Update_Status SceneIntro::PostUpdate() 
{
	SDL_Rect rect = palmeras.GetCurrentFrame();
	SDL_Rect rect2 = disco.GetCurrentFrame();
	SDL_Rect rect3 = titulo.GetCurrentFrame();
	SDL_Rect rect4 = subtitulo.GetCurrentFrame();
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &rect);
	App->render->Blit(bgTexture, 7, 37, &rect3);
	App->render->Blit(bgTexture, 27, 16, &rect4);
	app->render->Bliy(bgTexture, shipPosition_x, shipPosition_y, &rect2);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
		return true;
}