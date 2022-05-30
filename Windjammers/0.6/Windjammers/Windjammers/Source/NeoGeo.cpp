#include "NeoGeo.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

NeoGeo::NeoGeo(bool startEnabled) : Module(startEnabled)
{
	// Neo Geo Logo
	NeoGeoA.PushBack({ 106,   0,  20, 38 });
	NeoGeoA.PushBack({ 325,   0,  32, 41 });
	NeoGeoA.PushBack({ 546,   0,  47, 42 });
	NeoGeoA.PushBack({ 766,   0,  62, 40 });
	NeoGeoA.PushBack({ 984,   0,  74, 39 });
	NeoGeoA.PushBack({  30,  53,  88, 40 });
	NeoGeoA.PushBack({ 249,  53, 102, 39 });
	NeoGeoA.PushBack({ 467,  53, 115, 39 });
	NeoGeoA.PushBack({ 688,  53, 130, 39 });
	NeoGeoA.PushBack({ 899,  53, 177, 47 });
	NeoGeoA.PushBack({   6, 106, 148, 41 });
	NeoGeoA.PushBack({ 217, 106, 181, 43 });
	NeoGeoA.PushBack({ 438, 106, 191, 42 });
	NeoGeoA.PushBack({ 657, 106, 202, 41 });
	NeoGeoA.PushBack({ 877, 106, 220, 40 });
	NeoGeoA.PushBack({   1, 165, 229, 42 });
	NeoGeoA.PushBack({ 228, 165, 230, 40 });
	NeoGeoA.PushBack({ 455, 165, 230, 40 });
	NeoGeoA.PushBack({ 682, 165, 231, 36 });
	NeoGeoA.PushBack({ 911, 165, 231, 25 });
	NeoGeoA.PushBack({   3, 224, 225, 32 });
	NeoGeoA.PushBack({ 229, 225, 230, 29 });
	NeoGeoA.PushBack({ 453, 225, 227, 24 });
	NeoGeoA.PushBack({ 679, 226, 231, 22 });
	NeoGeoA.PushBack({ 907, 230, 231, 22 });
	NeoGeoA.PushBack({   2, 271, 226, 18 });
	NeoGeoA.PushBack({ 229, 271, 299, 19 });
	NeoGeoA.PushBack({ 456, 272, 227, 13 });
	NeoGeoA.PushBack({ 682, 272, 226, 10 });
	NeoGeoA.PushBack({ 909, 272, 228, 10 });
	NeoGeoA.PushBack({   6, 304, 208, 12 });
	NeoGeoA.PushBack({ 215, 302, 235, 12 });
	NeoGeoA.PushBack({ 450, 303, 225,  7 });
	NeoGeoA.PushBack({ 674, 302, 225, 10 });
	NeoGeoA.PushBack({ 902, 301, 238, 12 });
	NeoGeoA.PushBack({   3, 318, 230, 16 });
	NeoGeoA.PushBack({ 231, 318, 228, 16 });
	NeoGeoA.PushBack({ 472, 318, 226, 20 });
	NeoGeoA.PushBack({ 698, 318, 227, 21 });
	NeoGeoA.PushBack({ 925, 316, 229, 26 });
	NeoGeoA.PushBack({   3, 358, 224, 24 });
	NeoGeoA.PushBack({ 226, 356, 229, 30 });
	NeoGeoA.PushBack({ 454, 355, 229, 33 });
	NeoGeoA.PushBack({ 680, 354, 321, 34 });
	NeoGeoA.PushBack({ 910, 355, 233, 41 });

	NeoGeoA.speed = 0.2f;
	NeoGeoA.loop = false;

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

NeoGeo::~NeoGeo()
{

}

// Load assets
bool NeoGeo::Start()
{
	LOG("Loading background assets");

	bool ret = true;


	//Anims on top of bg
	NeoGeoLOGO = App->textures->Load("Assets/Sprites/Start1def.png");
	MaxLOGO = App->textures->Load("Assets/Sprites/Start5.png");

	bgTexture_white = App->textures->Load("Assets/Sprites/white.png");
	bgTexture_black = App->textures->Load("Assets/Sprites/black.png");

	currentAnimation = &NeoGeoA;
	//currentAnimation = &Max;

	App->audio->PlayMusic("Assets/Music/Neo Geo AESMVS Intro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status NeoGeo::Update()
{


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 40);
	}


	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status NeoGeo::PostUpdate()
{
	SDL_Rect rect = NeoGeoA.GetCurrentFrame();
	SDL_Rect rect2 = Max.GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture_white, 0, 0, NULL);
	App->render->Blit(NeoGeoLOGO, 43, 50, &rect, false);
	//App->render->Blit(bgTexture_black, 0, 0, NULL);
	App->render->Blit(MaxLOGO, 50, 200, &rect2, false);

	return Update_Status::UPDATE_CONTINUE;
}

