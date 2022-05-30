#ifndef __MAP_MENU_H__
#define __MAP_MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class MapMenu : public Module
{
public:
	MapMenu(bool startEnabled);

	~MapMenu();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

public:

	SDL_Texture* bgTexture = nullptr;

	struct scenarioSelected {
		bool Locked = false;
		int scenario = 0;
		int speed = 500;
		Particle selector;
		Scenario FinalSelection;
	};

	uint selected = 0;

	scenarioSelected Selector;

};

#endif // __MAP_MENU_H__