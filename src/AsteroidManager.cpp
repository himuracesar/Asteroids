#include <iostream>

#include "AsteroidManager.h"

Asteroid* AsteroidManager::asteroids[AsteroidManager::MAX_ASTEROIDS] = {0};

/**
* Destruye un asteroide
*/
void AsteroidManager::destroyAsteroid(int id)
{
	for(int index = 0; index < MAX_ASTEROIDS; index++)
	{
		if(asteroids[index] != NULL)
		{
			if(asteroids[index]->getID() == id)
			{
				asteroids[index] = NULL;

				break;
			}
		}
	}
}

/**
* Obtiene un asteroide
* @param index Es el indice del array donde se encuentra el asteroide
*/
Asteroid* AsteroidManager::getAsteroid(int index)
{
	return &(*asteroids[index]);
}

/**
* Agrega un asteroide
* @param asteroid Es el asteroide a agregar
*/
void AsteroidManager::addAsteroid(Asteroid* asteroid)
{
	for(int index = 0; index < MAX_ASTEROIDS; index++)
	{
		if(asteroids[index] == NULL)
		{
			asteroid->setID(index);
			asteroids[index] = asteroid;
			
			break;
		}
	}
}

/**
* Obtiene los espacios disponibles para poder crear nuevos asteroides
*/
int AsteroidManager:: getSpaces()
{
	int cont = 0;

	for(int inx = 0; inx < MAX_ASTEROIDS; inx++)
	{
		if(asteroids[inx] != NULL)
		{
			if(asteroids[inx]->getType() == Asteroid::BIG)
				cont += 2;
			else
				cont++;
		}
	}

	return MAX_ASTEROIDS - cont;
}

void AsteroidManager::reset()
{
	for(int index = 0; index < MAX_ASTEROIDS; index++)
	{
		if(asteroids[index] != NULL)
			delete asteroids[index];

		asteroids[index] = NULL;
	}
}