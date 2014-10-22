#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Box2D/Box2D.h>
#include <io.h>
#include <map>
#include <SDL_mixer.h>
using namespace std;

class Player
{
private:
	SDL_Texture* playerImg;
	b2Vec2 position;

public:
	Player();
	Player(b2Vec2 pos);
	~Player(void);
	void Update();
	void setPosition(b2Vec2 value);
	b2Vec2 getPosition();
	void LoadImages(SDL_Renderer* gRenderer,std::string name);
	void DrawImage(SDL_Renderer* gRenderer);
};
