#include "Crosshair.h"
#include "Engine.h"

Crosshair::Crosshair(SDL_Renderer* renderer)
{
	Vector2 cursorPosition = { 0, 0 };
	crosshairTexture.LoadFromFile(renderer, "resources/crosshair.png");
	width = crosshairTexture.GetWidth();
	height = crosshairTexture.GetHeight();
	SDLTexture = crosshairTexture.GetTexture();
}

Crosshair::~Crosshair()
{

}

void Crosshair::HandleInput(Input* input)
{
	Vector2* mousePos = input->GetMousePosition();
	cursorPosition.X = mousePos->X - (width / 2);
	cursorPosition.Y = mousePos->Y - (height / 2);
}

SDL_Texture *Crosshair::getCrosshairTexture()
{
	return SDLTexture;
}

void Crosshair::Render(SDL_Renderer *renderer)
{
	SDL_Rect renderQuad = { cursorPosition.X, cursorPosition.Y, width, height };
	SDL_RenderCopy(renderer, SDLTexture, NULL, &renderQuad);
}
