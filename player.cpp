#include "player.h"
#include "Engine.h"

player::player(SDL_Renderer* mRenderer)
{
		mPlayerTexture.loadFromFile(mRenderer, "resources/playerSprite_2.png");
		mWidth = mPlayerTexture.getWidth();
		mHeight = mPlayerTexture.getHeight();

		mPosX = (Engine::getScreenWidth() / 2) - (mWidth / 2);
		mPosY = (Engine::getScreenHeight() /2) - (mHeight / 2);
		moveSpeed = 10;

		mSDLTexture = mPlayerTexture.getTexture();
}

player::~player()
{
	
}

//Texture* player::render(SDL_Rect* spriteClip , double angle, SDL_Point* center, SDL_RendererFlip spriteFlip)
//{
//	mRenderTexture = nullptr;
//	SDL_Rect renderQuad = { mWidth, mHeight };
//	if (spriteClip != nullptr)
//	{
//		renderQuad.w = spriteClip->w;
//		renderQuad.h = spriteClip->h;
//
//	}
//
//
//}

void player::handleInput() 
{
	if (Input::keyPressed(MOVE_UP))
	{
		movePlayer(Y, -moveSpeed);
	}
	if (Input::keyPressed(MOVE_DOWN))
	{
		movePlayer(Y, moveSpeed);
	}
	if (Input::keyPressed(MOVE_LEFT))
	{
		movePlayer(X, -moveSpeed);
	}
	if (Input::keyPressed(MOVE_RIGHT))
	{
		movePlayer(X, moveSpeed);
	}
}

void player::movePlayer(Axis axis, int moveAmount) 
{
	if (axis == X) {
		mPosX += moveAmount;
	}
	else {
		mPosY += moveAmount;
	}
	if ((mPosX + (mWidth*0.5))> Engine::getScreenWidth())
	{
		mPosX = 0 - (mWidth*0.5);
	}
	else if ((mPosX + (mWidth*0.5)) < 0)
	{
		mPosX = Engine::getScreenWidth() - (mWidth*0.5);
	}
	else if ((mPosY + (mHeight*0.5)) > Engine::getScreenHeight())
	{
		mPosY = 0 - (mHeight*0.5);
	}
	else if ((mPosY + (mHeight*0.5)) < 0)
	{
		mPosY = Engine::getScreenHeight() - (mHeight*0.5);
	}
}

int player::getMoveSpeed() {
	return moveSpeed;
}
int player::mGetPosX(){
	return mPosX;
}

int player::mGetPosY() {
	return mPosY;	
}

SDL_Texture *player::getPlayerTexture() {
	return mSDLTexture;
}


void player::render(SDL_Renderer *mRenderer) {
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };
	SDL_RenderCopy(mRenderer, mSDLTexture, NULL, &renderQuad );
}