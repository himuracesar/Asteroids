#include "Player.h"
#include "Game.h"
#include "Font.h"
#include "ExplosionManager.h"
#include "Turbine.h"
#include "CheckCollision.h"
#include "AsteroidManager.h"

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_opengl.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define WIDTH_ICON_LIFE 20
#define HEIGHT_ICON_LIFE 20

#define DegreeToRad(n) n*0.017453292519943295769236907684886
#define RadToDegree(n) n*57.295779513082320876798154814105

/**
* Clase GamePlay
* @author Cesar Himura
*/
class GamePlay : public Game
{
	private:
		bool LEFT;
		bool RIGHT;
		bool UP, UP_OLD;
		bool DOWN, DOWN_OLD;
		bool FIRE;
		bool FIRE_OLD;
		bool P, P_OLD;
		int ciclos;
		int gs;
		int optionPause;
		int explosionsPlayer;
		char score[10];
		Mix_Music *music;
		Mix_Chunk *shot;
		Mix_Chunk *explosionSound;

		Player *player;
		Font *fontScore;
		Font *fontPause;
		//Turbine *turbine;
		GLuint iconLife;
		GLuint life_texture;

		const static int GAME_PLAY = 0;
		const static int GAME_OVER = 1;
		const static int PAUSE = 2;
		const static int PAUSE_MENU = 1;
		const static int PAUSE_CONTINUE = 0;

		/*** FUNCIONES ***/
		void createAsteroids();
		void initPlayer();
		void updateGamePlay(SDL_Event event);
		void updatePause(SDL_Event event);
		void updateGameOver(SDL_Event event);
		void renderGamePlay();
		void renderPause();
		void renderGameOver();
		void GenerateIconLife();
		void loadTexture(GLuint *texture, const char *file);

	public:
		GamePlay();
		~GamePlay();
		virtual void init();
		virtual void update(SDL_Event event);
		virtual void render();
};