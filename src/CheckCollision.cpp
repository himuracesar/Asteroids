#include "CheckCollision.h"
#include "AsteroidManager.h"
#include "Player.h"

#include <iostream>

int CheckCollision::score = 0;
int CheckCollision::highScore = 0;

/**
* Inicializo las variables que no fueron inicializadas en la cabecera. Por ser estaticas deben tener un valor
* por default ya que pueden ser consultadas sin haber una instancia de la clase.
*/
Sprite* CheckCollision::vAlly[CheckCollision::MAX_ALLY] = {0}; //Inicializa un array de punteros todos a NULL
Sprite* CheckCollision::vEnemy[CheckCollision::MAX_ENEMY] = {0};

/**
* Agrega un sprite a una estructura perteneciente a un equipo que checara las colisiones
* @param sprite Es el sprite que agregara
* @param team Es el equipo al que pertenecera el sprite a agregar
*/
void CheckCollision::addSprite(Sprite *sprite, int team)
{
	switch(team)
	{
		case ALLY:
			for(int ally = 0; ally < MAX_ALLY; ally++)
			{
				if(vAlly[ally] == NULL)
				{
					vAlly[ally] = sprite;
					break;
				}
			}
		break;

		case ENEMY:
			for(int enemy = 0; enemy < MAX_ENEMY; enemy++)
			{
				if(vEnemy[enemy] == NULL)
				{
					vEnemy[enemy] = sprite;
					break;
				}
			}
		break;
	}
}

/**
* Chaca si hay colisiones entre sprites de los diferentes equipos. El metodo empleado es el 
* Bounding Circle
*/
bool CheckCollision::check()
{
	double x1, y1, r1;
	double x2, y2, r2;
	
	for(int inx_ally = 0; inx_ally < MAX_ALLY; inx_ally++)
	{
		if(vAlly[inx_ally] != NULL)
		{
			x1 = vAlly[inx_ally]->getX();
			y1 = vAlly[inx_ally]->getY();
			r1 = vAlly[inx_ally]->getHeight()/2;

			for(int inx_enemy = 0; inx_enemy < MAX_ENEMY; inx_enemy++)
			{
				if(vEnemy[inx_enemy] != NULL)
				{
					x2 = vEnemy[inx_enemy]->getX();
					y2 = vEnemy[inx_enemy]->getY();
					r2 = vEnemy[inx_enemy]->getWidth()/2;

					if((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) <= (r1+r2)*(r1+r2))
					{
						//std::cout << "..::COLLISION::.." << std::endl;

 						if(vAlly[inx_ally]->getName() == "Player")
						{
							((Player*)vAlly[inx_ally])->OnCollide(((Asteroid*)vEnemy[inx_enemy])->getType());
						}
						else
						{
							((Shot*)vAlly[inx_ally])->OnCollide();

							vAlly[inx_ally] = NULL;

							if(ExplosionManager::getSpaces() > 0)
							{
								ExplosionManager::addExplosion(new Explosion(((Asteroid*)vEnemy[inx_enemy])->getX(),
									                                         ((Asteroid*)vEnemy[inx_enemy])->getY()));
							}
						}

						((Asteroid*)vEnemy[inx_enemy])->OnCollide();

						if(((Asteroid*)vEnemy[inx_enemy])->getType() == Asteroid::DESTROY)
						{
							if(ExplosionManager::getSpaces() > 0)
							{
								ExplosionManager::addExplosion(new Explosion(((Asteroid*)vEnemy[inx_enemy])->getX(),
									                                         ((Asteroid*)vEnemy[inx_enemy])->getY()));
							}

							delete vEnemy[inx_enemy];

							vEnemy[inx_enemy] = NULL;
							//std::cout << ".::Asteroide Destruido::. " << std::endl;

							score += 15;
						}
						else
							if(((Asteroid*)vEnemy[inx_enemy])->getType() == Asteroid::MEDIUM)
							{
								//std::cout << "Crea Asteroide MEDIUM" << std::endl;
								AsteroidManager::addAsteroid(new Asteroid("images/asteroid.png", Asteroid::MEDIUM, 
															 ((Asteroid*)vEnemy[inx_enemy])->getX()+40,
															 ((Asteroid*)vEnemy[inx_enemy])->getY()+40, 
									                         ((Asteroid*)vEnemy[inx_enemy])->getVx(), 
															 ((Asteroid*)vEnemy[inx_enemy])->getVy(), 
															 ((Asteroid*)vEnemy[inx_enemy])->getAngleDirection()));

								if(ExplosionManager::getSpaces() > 0)
								{
									ExplosionManager::addExplosion(new Explosion(((Asteroid*)vEnemy[inx_enemy])->getX(),
																				 ((Asteroid*)vEnemy[inx_enemy])->getY()));
								}

								score += 5;
							}
							else
							{
								if(ExplosionManager::getSpaces() > 0)
								{
									ExplosionManager::addExplosion(new Explosion(((Asteroid*)vEnemy[inx_enemy])->getX(),
																				 ((Asteroid*)vEnemy[inx_enemy])->getY()));
								}

								score += 10;
							}

						return true;
					}
				}//if vEnemy[] != NULL
			}
		}//if vAlly[] != NULL
	}

	return false;
}

/**
* Resetea las estructuras que son barridas para checar si existe alguna colision
*/
void CheckCollision::reset()
{
	for(int index = 0; index < MAX_ALLY; index++)
	{
		vAlly[index] = NULL;
	}

	for(int index = 0; index < MAX_ENEMY; index++)
	{
		vEnemy[index] = NULL;
	}
}

/**
* Obtiene un sprite de un determinado equipo
* @param index Es el indice donde se encuentra el sprite dentro de la estructura
* @param team Es el equipo al que pertences el sprite
*/
Sprite* CheckCollision::getSprite(int index, int team)
{
	switch(team)
	{
		case ALLY:
			return &(*vAlly[index]);
		break;

		case ENEMY:
			return &(*vEnemy[index]);
		break;
	}

	return NULL;
}

/**
* Borra un sprite de un equipo de sprites que son colisionables 
* @param idSprite ID del sprite a borrar
* @param team Es el equipo de donde sera borrado el sprite
*/
void CheckCollision::deleteSprite(int idSprite, int team)
{
	switch(team)
	{
		case ALLY:
			for(int index = 0; index < MAX_ALLY; index++)
			{
				if(vAlly[index] != NULL)
					if(vAlly[index]->getName() == "Shot")
						if(((Shot*)(vAlly[index]))->getId() == idSprite)
						{
							vAlly[index] = NULL;
							break;
						}
			}
		break;

		case ENEMY:
			for(int index = 0; index < MAX_ENEMY; index++)
			{
				if(vEnemy[index] != NULL)
					if(vEnemy[index]->getName() == "Shot")
						if(((Shot*)(vEnemy[index]))->getId() == idSprite)
						{
							vEnemy[index] = NULL;
							break;
						}
			}
		break;
	}
}