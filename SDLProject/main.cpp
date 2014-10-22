//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Player.h"
#include <Box2D\Box2D.h>
#include "Net.h"
#include <iostream>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//The window we'll be rendering to 
SDL_Window* gWindow = NULL; 

SDL_Renderer* gRenderer;
Player * m_Player;
Player * m_Player_2;

Net * network;
std::string RecievingIP;
std::string RecievingPort;
std::string personalIP;
std::string personalPort;
bool IT;
SDL_Texture* gameOverImage;
float time1 = 0.0;
float time2 = 0.0;
void NetWorkSetup()
{
	std::cout << "Enter Your ip" << endl;
	cin>>personalIP;
	std::cout << "Enter Your port" << endl;
	cin>>personalPort;
	
	network->setupUDP(atoi(personalPort.c_str()),(char *)personalIP.c_str());
	std::cout << "Are you IT" << endl;
	std::string it;
	cin>>it;
	if(it == "yes" || it == "Yes" || it == "YES")
	{
		IT = true;
	}
	else
	{
		IT = false;
	}
	std::cout << "Enter Opponents ip" << endl;
	cin>>RecievingIP;
	std::cout << "Enter Opponents port" << endl;
	cin>>RecievingPort;
}

void SendMessage(b2Vec2 pos)
{	
	std::string position = std::to_string(pos.x) + "+" + std::to_string(pos.y) + "+";
	network->sendData((char *)RecievingIP.c_str(), atoi(RecievingPort.c_str()),(char *)position.c_str() );
	//network->sendData("149.153.102.41", 28001,(char *)position.c_str() );
}

/*void SendMessage(char * string)
{	
	network->sendData("149.153.102.41", 28001, string );
}*/

bool Collision(b2Vec2 pos1, b2Vec2 pos2)
{
	float num = ((pos2.x - pos1.x) * (pos2.x - pos1.x)) + ((pos2.y - pos1.y) * (pos2.y - pos1.y));
	float distance = std::sqrt(num);
	if(distance < 25)
	{
		return true;
	}
	return false;
}

int main( int argc, char* args[] )
{
	SDL_Event e;
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
		
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	
	network = new Net();
	network->initialise();

	NetWorkSetup();

	m_Player = new Player(b2Vec2(320,240));
	m_Player_2 = new Player(b2Vec2(120,240));
	m_Player->LoadImages(gRenderer,"player.png");
	m_Player_2->LoadImages(gRenderer,"player2.png");
	bool quit = false;
	time1 =SDL_GetTicks()/1000;
	while(quit == false)
	{
				//this calls any methods that need to loop in game manager
		SDL_PollEvent( &e );
		SDL_RenderClear( gRenderer );
		m_Player->Update();
		m_Player->DrawImage(gRenderer);
		char message [100] = "";
		if (network->receiveData(message) != 0)
		{
			std::stringstream ss(message);
			std::string name;
			std::getline(ss, name, '+');
			std::string item( name);
			b2Vec2 pos = b2Vec2(std::stof(item),0.0f);
			std::getline(ss, name, '+');
			std::string item2( name);
			pos.y = std::stof(item2);
			m_Player_2->setPosition(pos);
			//string[] tokens = message.split(delims);
		}


		m_Player_2->DrawImage(gRenderer);
		if(Collision(m_Player->getPosition(),m_Player_2->getPosition()))
		{
			//break;
			//int hi= 9;
		}
		SendMessage(m_Player->getPosition());
		SDL_RenderPresent( gRenderer );
		time2 = SDL_GetTicks()/1000;
	}
	float totalTime = time2 - time1;
	cout << "Game over the time is " + std::to_string( totalTime) << endl;
	if(IT == true)
	{
		gameOverImage = IMG_LoadTexture(gRenderer, "You Win.png");
	}
	else
	{
		gameOverImage = IMG_LoadTexture(gRenderer, "gameover.png");
	}
	
	while(true)
	{
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = 640; 
		stretchRect.h = 480;
		SDL_RenderCopy( gRenderer, gameOverImage, NULL, &stretchRect );
		SDL_RenderPresent( gRenderer );
	}

	return 0; 
}


