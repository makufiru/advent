#pragma once
#include <vector>
#include "Projectile.h"
#include "Texture.h"

class player;

class Weapons
{
public:
	Weapons(SDL_Renderer *renderer);
	void Render(SDL_Renderer *renderer);
	void Shoot(Vector2 position, Vector2 direction, double angle);
	void Update();
	//vector to contain projectiles
	std::vector<Projectile> projectiles;

private:
	SDL_Renderer *renderer;
};