#ifndef SHOT_H
	#define SHOT_H

#include "Sprite.h"

/**
* Clase que maneja la logica del disparo de la nave
*/
class Shot : public Sprite
{
	public:
		Shot(char *file);
		~Shot();
		void virtual update();
		void OnCollide();
		void setId(int id){this->id = id;};
		static const int MAX_SPEED = 13;
		int getId(){return id;};

	private:
		int id;
};

#endif;