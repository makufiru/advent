#include "Player.h"
#include "Engine.h"

Player::Player(SDL_Renderer* renderer)
{
	blaster = new Weapons(renderer);
	playerTexture.LoadFromFile(renderer, "resources/player_ship.png");
	width = playerTexture.GetWidth();
	height = playerTexture.GetHeight();
	SpriteAngle = 0.0;

	position.X = (Engine::GetScreenWidth() / 2) - (width / 2);
	position.Y = (Engine::GetScreenHeight() / 2) - (height / 2);
	moveSpeed = 0.5;
	maxMoveSpeed = 15;
	shotInterval = 150;

	SDLTexture = playerTexture.GetTexture();
	lastShotTime = 0;
}

Player::~Player()
{

}

//handles key presses and mouse clicks 
void Player::HandleInput(Input* input)
{
	// vertical
	if (input->KeyPressed(MOVE_UP) && velocity.Y > -maxMoveSpeed) {
		velocity.Y -= moveSpeed;
	}
	else if (input->KeyPressed(MOVE_DOWN) && velocity.Y < maxMoveSpeed) {
		velocity.Y += moveSpeed;
	}
	else {
		velocity.Y = velocity.Y * 0.95;
	}
	
	// horizontal
	if (input->KeyPressed(MOVE_LEFT) && velocity.X > -maxMoveSpeed) {
		velocity.X -= moveSpeed;
	}
	else if (input->KeyPressed(MOVE_RIGHT) && velocity.X < maxMoveSpeed) {
		velocity.X += moveSpeed;
	}
	else {
		velocity.X = velocity.X * 0.95;
	}

	// shooting
	if (input->KeyPressed(SHOOT))
	{
		currentTime = SDL_GetTicks();
		if ((currentTime - lastShotTime) > shotInterval)
		{
			shoot();
			lastShotTime = SDL_GetTicks();
		}
	}

	//Calculate the angle to the mouse cursor and set the player rotation accordingly
	mousePosition = input->GetMousePosition();
	playerCenter = { position.X + width / 2, position.Y + height / 2 };
	Vector2 delta = { mousePosition->X - playerCenter.X, mousePosition->Y - playerCenter.Y };

	angle = atan2(delta.Y, delta.X) * 180 / M_PI;
	angle += 90.0; //Add 90 to rotate the texture correctly

}

void Player::checkBoundaries()
{
	if ((position.X + (width*0.5))> Engine::GetScreenWidth())
	{
		position.X = 0 - (width*0.5);
	}
	else if ((position.X + (width*0.5)) < 0)
	{
		position.X = Engine::GetScreenWidth() - (width*0.5);
	}
	else if ((position.Y + (height*0.5)) > Engine::GetScreenHeight())
	{
		position.Y = 0 - (height*0.5);
	}
	else if ((position.Y + (height*0.5)) < 0)
	{
		position.Y = Engine::GetScreenHeight() - (height*0.5);
	}
}

void Player::movePlayer()
{
	position.X += velocity.X;
	position.Y += velocity.Y;
}

int Player::getMoveSpeed()
{
	return moveSpeed;
}

Vector2 Player::GetPosition() const
{
	return position;
}

SDL_Texture *Player::GetPlayerTexture()
{
	return SDLTexture;
}

void Player::Render(SDL_Renderer *renderer)
{
	blaster->Render(renderer);
	SDL_Rect renderQuad = { position.X, position.Y, width, height };
	SDL_RenderCopyEx(renderer, SDLTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}

void Player::shoot()
{
	Vector2 directionVector = { mousePosition->X - playerCenter.X, mousePosition->Y - playerCenter.Y };
	Vector2 normalizedDirection = directionVector.Normalize();
	Vector2 direction = { normalizedDirection.X * width / 2 , normalizedDirection.Y * width / 2 };
	Vector2 bulletPos = { playerCenter.X + direction.X, playerCenter.Y + direction.Y };
	blaster->Shoot(bulletPos, direction, angle);
}

void Player::Update()
{
	movePlayer();
	checkBoundaries();
	blaster->Update();
}