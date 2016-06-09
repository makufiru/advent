#include "Texture.h"




Texture::Texture()
{
	texture = nullptr;
	width = 0;
	height = 0;

}

Texture::~Texture()
{
	Free();
}


bool Texture::LoadFromFile(SDL_Renderer* gRenderer, const std::string path)
{
	Free();

	//final texture
	SDL_Texture* finalTexture = nullptr;

	//load the file
	finalTexture = IMG_LoadTexture(gRenderer, path.c_str());
	if (finalTexture == nullptr)
	{
		printf("failed to load image. SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		int w, h;

		if (SDL_QueryTexture(finalTexture, NULL, NULL, &w, &h) != 0)
		{
			printf("failed to query texture. you're not gonna know shit about it.");
		}
		else
		{
			width = w;
			height = h;
		}
	}

	//sets our suface turned texture to our member vairable texture.
	texture = finalTexture;
	return texture != nullptr;


}


void Texture::Free()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;

		width = 0;
		height = 0;
	}
}


float Texture::GetWidth()
{
	return width;
}

float Texture::GetHeight()
{
	return height;
}

SDL_Texture* Texture::GetTexture()
{
	return texture;
}

