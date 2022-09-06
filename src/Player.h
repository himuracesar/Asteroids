#ifndef PLAYER_H
	#define PLAYER_H

#include "Sprite.h"
#include "Shot.h"
#include "Asteroid.h"

/**
* Clase Player
*/
class Player : public Sprite
{
	public:
		Player(char *file);
		~Player();
		void virtual update();
		void virtual render();
		void fire();
		void OnCollide(int type);
		void destroyShot(int id);
		void setLife(int life){this->life = life;};
		void setLifes(int lifes){this->lifes = lifes;};
		void setState(int state){this->state = state;};
		int getLife(){return life;};
		int getLifes(){return lifes;};
		int getState(){return state;};

		static const int SPEED_ROTATE = 2;
		static const int MAX_SPEED = 7;
		static const int ACCEL = 1;
		static const int MAX_SHOTS = 5;
		static const int EXPLODE = 0;
		static const int LIVE = 1;

	private:
		Shot* shots[MAX_SHOTS];
		int idShot;
		int life;
		int lifes;
		int state;
};

#endif;