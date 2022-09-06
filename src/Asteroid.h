#ifndef ASTEROID_H
	#define ASTEROID_H
#include "Sprite.h"

/**
* Clase Asteroide
* @author Cesar Himura
*/
class Asteroid : public Sprite
{
	public:
		Asteroid(char *file, int type);
		Asteroid(char *file, int type, double x, double y, double vx, double vy, double angleDir);
		~Asteroid();
		void virtual update();
		void setAngleDirection(int angle){angle_dir = angle;};
		void OnCollide();
		void setType(int type){this->type = type;};
		void setID(int id){this->id = id;};
		int getAngleDirection(){return angle_dir;};
		int getType(){return type;};
		int getID(){return id;};
		static const int RANDOM = 0;
		static const int BIG = 1;
		static const int MEDIUM = 2;
		static const int LITTLE = 3;
		static const int DESTROY = 4;

	private:
		int angle_dir;
		int type;
		int id;
};

#endif;