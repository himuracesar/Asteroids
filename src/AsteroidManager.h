#include "Asteroid.h"

/**
* Es la clase que maneja la creacion de los asteroides
*/
class AsteroidManager
{
	public:
		static const int MAX_ASTEROIDS = 8;
		static void destroyAsteroid(int id);
		static void addAsteroid(Asteroid* asteroid);
		static void reset();
		static Asteroid* getAsteroid(int index);
		static int getSpaces();

	private:
		static Asteroid* asteroids[MAX_ASTEROIDS];
};