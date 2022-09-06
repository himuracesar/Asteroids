//#include "Asteroid.h"

class AsteroidManager
{
	private:
		//static int cont = 0;
		static Asteroid* asteroids[MAX_ASTEROIDS];

	public:
		static const int MAX_ASTEROIDS = 8;
		static void destroyAsteroid(int id);
		static void addAsteroid(Asteroid* asteroid);
		static Asteroid* getAsteroid(int index);
};