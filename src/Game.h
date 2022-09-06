#ifndef GAME_H
	#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

/**
* Clase Padre del framework sus hijos son los game states del juego
* @author Cesar Himura
*/
class Game
{
	private:
		int gameState;
		int gameStateOld;
		bool regulateKey;
		GLuint texture; //this is a handle to our texture object
		GLuint background;
		GLenum texture_format;
		GLint nofcolors;

	public:
		Game();
		virtual ~Game();
		virtual void init();
		virtual void update(SDL_Event event);
		virtual void render();
		void setGameState(int gameState){this->gameState = gameState;};
		void setGameStateOld(int gameStateOld){this->gameStateOld = gameStateOld;};
		void setRegulateKey(bool regulateKey){this->regulateKey = regulateKey;};
		int getGameState(){return gameState;};
		int getGameStateOld(){return gameStateOld;};
		int setBackground(char* img);
		bool isRegulateKey(){return regulateKey;};

		const static int MENU = 0;
		const static int GAME_PLAY = 1;
		const static int INSTRUCTIONS = 2;
		const static int EXIT = 3;
		const static int SPLASH = 4;
		const static int CREDITS = 5;

		const static int WIDTH_SCREEN = 800;
		const static int HEIGHT_SCREEN = 600;
};

#endif
