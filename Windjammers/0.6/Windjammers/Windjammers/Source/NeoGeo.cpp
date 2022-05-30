#include "NeoGeo.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

NeoGeo::NeoGeo(bool startEnabled) : Module(startEnabled)
{

	//Neo Geo Logo
	NeoGeo.PushBack({ 106, 0, 20, 38 });
	NeoGeo.PushBack({ 325, 0, 32, 41 });
	NeoGeo.PushBack({ 546, 0, 47, 42 });
	NeoGeo.PushBack({ 766, 0, 62, 40 });
	NeoGeo.PushBack({ 984, 0, 74, 39 });
	NeoGeo.PushBack({ 30, 53, 88, 40 });
	NeoGeo.PushBack({ 249, 53, 102, 39 });
	NeoGeo.PushBack({ 467, 53, 115, 39 });
	NeoGeo.PushBack({ 688, 53, 130, 39 });
	NeoGeo.PushBack({ 899, 53, 177, 47 });
	NeoGeo.PushBack({ 6, 106, 148, 41 });
	NeoGeo.PushBack({ 217, 106, 181, 43 });
	NeoGeo.PushBack({ 438, 106, 191, 42 });
	NeoGeo.PushBack({ 657, 106, 202, 41 });
	NeoGeo.PushBack({ 877, 106, 220, 40 });
	NeoGeo.PushBack({ 1, 165, 229, 42 });
	NeoGeo.PushBack({ 228, 165, 230, 40 });
	NeoGeo.PushBack({ 455, 165, 230, 40 });
	NeoGeo.PushBack({ 682, 165, 231, 36 });
	NeoGeo.PushBack({ 911, 165, 231, 25 });
	NeoGeo.PushBack({ 3, 224, 225, 32 });
	NeoGeo.PushBack({ 229, 225, 230, 29 });
	NeoGeo.PushBack({ 453, 225, 227, 24 });
	NeoGeo.PushBack({ 679, 226, 231, 22 });
	NeoGeo.PushBack({ 907, 230, 231, 22 });
	NeoGeo.PushBack({ 2, 271, 226, 18 });
	NeoGeo.PushBack({ 229, 271, 299, 19 });
	NeoGeo.PushBack({ 456, 272, 227, 13 });
	NeoGeo.PushBack({ 682, 272, 226, 10 });
	NeoGeo.PushBack({ 909, 272, 228, 10 });
	NeoGeo.PushBack({ 6, 304, 208, 12 });
	NeoGeo.PushBack({ 215, 302, 235, 12 });
	NeoGeo.PushBack({ 450, 303, 225, 7 });
	NeoGeo.PushBack({ 674, 302, 225, 10 });
	NeoGeo.PushBack({ 902, 301, 238, 12 });
	NeoGeo.PushBack({ 3, 318, 230, 16 });
	NeoGeo.PushBack({ 231, 318, 228, 16 });
	NeoGeo.PushBack({ 472, 318, 226, 20 });
	NeoGeo.PushBack({ 698, 318, 227, 21 });
	NeoGeo.PushBack({ 925, 316, 229, 26 });
	NeoGeo.PushBack({ 3, 358, 224, 24 });
	NeoGeo.PushBack({ 226, 356, 229, 30 });
	NeoGeo.PushBack({ 454, 355, 229, 33 });
	NeoGeo.PushBack({ 680, 354, 321, 34 });
	NeoGeo.PushBack({ 910, 355, 233, 41 });

	NeoGeo.speed = 0.4f;
	NeoGeo.loop = false;

	//Max logo
	Max.PushBack({ 227, 103, 24, 37 });
	Max.PushBack({ 251, 103, 24, 39 });
	Max.PushBack({ 275, 103, 24, 36 });
	Max.PushBack({ 299, 103, 24, 35 });
	Max.PushBack({ 323, 103, 24, 36 });
	Max.PushBack({ 347, 103, 23, 36 });
	Max.PushBack({ 370, 103, 23, 35 });
	Max.PushBack({ 393, 103, 23, 36 });
	Max.PushBack({ 227, 103, 24, 37 });
	Max.PushBack({ 251, 103, 24, 39 });
	Max.PushBack({ 275, 103, 24, 36 });
	Max.PushBack({ 299, 103, 24, 35 });
	Max.PushBack({ 323, 103, 24, 36 });
	Max.PushBack({ 347, 103, 23, 36 });
	Max.PushBack({ 370, 103, 23, 35 });
	Max.PushBack({ 393, 103, 23, 36 });
	Max.PushBack({ 227, 103, 24, 37 });
	Max.PushBack({ 251, 103, 24, 39 });
	Max.PushBack({ 275, 103, 24, 36 });
	Max.PushBack({ 299, 103, 24, 35 });
	Max.PushBack({ 323, 103, 24, 36 });
	Max.PushBack({ 347, 103, 23, 36 });
	Max.PushBack({ 370, 103, 23, 35 });
	Max.PushBack({ 393, 103, 23, 36 });
	Max.PushBack({ 227, 103, 24, 37 });
	Max.PushBack({ 251, 103, 24, 39 });
	Max.PushBack({ 275, 103, 24, 36 });
	Max.PushBack({ 299, 103, 24, 35 });
	Max.PushBack({ 323, 103, 24, 36 });
	Max.PushBack({ 347, 103, 23, 36 });
	Max.PushBack({ 370, 103, 23, 35 });
	Max.PushBack({ 393, 103, 23, 36 });
	Max.speed = 0.4f;
	Max.loop = false;
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool NeoGeo::Start()
{
	LOG("Loading background assets");

	bool ret = true;


	//Anims on top of bg
	NeoGeoLOGO = App->textures->Load("Assets/Spriteswind/Sprites/UI/Start1def.png");
	MaxLOGO = App->textures->Load("Assets/Spriteswind/Sprites/UI/Start5.png");

	bgTexture_white = App->textures->Load("Assets/Spriteswind/Sprites/UI/Dont_Use/introbg_white.png");
	bgTexture_black = App->textures->Load("Assets/Spriteswind/Sprites/UI/Dont_Use/introbg_black.png");

	currentAnimation = &NeoGeo;
	//currentAnimation = &Max;

	App->audio->PlayMusic("Assets/Music/Neo Geo AESMVS Intro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status NeoGeo::Update()
{


	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->SceneIntro, 40);
	}


	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status NeoGeo::PostUpdate()
{
	SDL_Rect rect = NeoGeo.GetCurrentFrame();
	SDL_Rect rect2 = Max.GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture_white, 0, 0, NULL);
	App->render->Blit(NeoGeoLOGO, 43, 50, &rect, false);
	//App->render->Blit(bgTexture_black, 0, 0, NULL);
	App->render->Blit(MaxLOGO, 50, 200, &rect2, false);

	return Update_Status::UPDATE_CONTINUE;
}
