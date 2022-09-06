#ifndef MENU_H
    #define MENU_H

#include "Game.h"
#include "Font.h"
#include "CheckCollision.h"
#include "SDL_mixer.h"

#include "SDL.h"

#include <string>

class Menu : public Game
{
	private:
		Font *fontOptions;
		Font *fontHS;
		int option;
		int canal;
		const static int NUM_OPTIONS = 3;
		bool UP, DOWN, UP_OLD, DOWN_OLD, ENTER, ENTER_OLD;
		char highScore[10];
		std::string sHighScore;
		Mix_Music *music;
		Mix_Chunk *menuMove;
		Mix_Chunk *menuSelect;

	public:
		Menu(bool regulateKey);
		~Menu();
		virtual void init();
		virtual void update(SDL_Event event);
		virtual void render();
};

#endif