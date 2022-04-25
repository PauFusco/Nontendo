#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "../External_Libraries/SDL/include/SDL_rect.h"

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		DISC,
		RED,
		PLAYER_SHOT,
		ENEMY_SHOT,
		GOAL,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	Type returnt() {
		return type;
	}

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};


#endif // !__COLLIDER_H__

