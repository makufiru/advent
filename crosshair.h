#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include "SDL.h"
#include "Input.h"
#include "Player.h"

class Crosshair
{
public:
	Crosshair(SDL_Renderer *renderer);
	~Crosshair();
	SDL_Texture* getCrosshairTexture();
	void Render(SDL_Renderer *mRenderer);
	void HandleInput(Input *input);

private:
	Texture crosshairTexture;
	SDL_Texture *SDLTexture;
	SDL_Renderer *Renderer;
	SDL_Rect SpriteClips[1];
	Texture renderTexture;
	int width;
	int height;
	Vector2 cursorPosition;
};