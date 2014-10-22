#include "Player.h"
#include <iostream>


Player::Player()
{
	//const int SCREEN_WIDTH = 640;
	//const int SCREEN_HEIGHT = 480;
	position = b2Vec2(320,240);
}

Player::~Player(void)
{
}

void Player::Update()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	

	
	if( currentKeyStates[ SDL_SCANCODE_UP ] ) 
	{
		position.y -= 0.1f;
	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) 
	{
		position.y += 0.1f;
	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) 
	{
		position.x -= 0.1f;
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) 
	{
		position.x += 0.1f;
	}
}




void Player::LoadImages(SDL_Renderer* gRenderer,std::string name)
{
	const char * c = name.c_str();
	playerImg = IMG_LoadTexture(gRenderer, c);
}

void Player::DrawImage(SDL_Renderer* gRenderer)
{

	SDL_Rect stretchRect;
	stretchRect.x = position.x;
	stretchRect.y = position.y;
	stretchRect.w = 25; 
	stretchRect.h = 25;
	SDL_RenderCopy( gRenderer, playerImg, NULL, &stretchRect );
	

}

void Player::setPosition(b2Vec2 value)
{
	position = value;
}

b2Vec2 Player::getPosition()
{
	return position;
}