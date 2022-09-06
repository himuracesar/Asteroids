#ifndef CHECKCOLLISION_H
	#define CHECKCOLLISION_H

#include "Sprite.h"
#include "ExplosionManager.h"

/**
* Clase que gestiona las colisiones
*/
class CheckCollision
{
	public:
		static void addSprite(Sprite *sprite, int team);
		static void deleteSprite(int idSprite, int team);
		static void reset();
		static void setScore(int sc){score = sc;};
		static void setHighScore(int sc){highScore = sc;};
		static bool check();
		static const int ALLY = 0;
		static const int ENEMY = 1;
		static const int MAX_ENEMY = 8;
		static const int MAX_ALLY = 6;
		static Sprite* getSprite(int index, int team);
		static int getScore(){return score;};
		static int getHighScore(){return highScore;};

	private:
		static Sprite* vEnemy[MAX_ENEMY];
		static Sprite* vAlly[MAX_ALLY];
		static int score;
		static int highScore;
};

#endif;