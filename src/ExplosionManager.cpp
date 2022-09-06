#include "ExplosionManager.h"

Explosion* ExplosionManager::explosions[ExplosionManager::MAX_EXPLOSIONS + MATRESS] = {0};

/**
* Agrega una nueva explosion
*/
void ExplosionManager::addExplosion(Explosion* explosion)
{
	for(int index = 0; index < MAX_EXPLOSIONS; index++)
	{
		if(explosions[index] == NULL)
		{
			explosions[index] = explosion;
			break;
		}
	}
}

/**
* Obtiene los espacios disponibles para poder crear nuevas explosiones
*/
int ExplosionManager::getSpaces()
{
	int cont = 0;

	for(int inx = 0; inx < MAX_EXPLOSIONS; inx++)
	{
		if(explosions[inx] != NULL)
		{
			cont++;
		}
	}

	return MAX_EXPLOSIONS - cont;
}

/**
* Actualiza todas las explosiones
*/
void ExplosionManager::update()
{
	for(int inx = 0; inx < MAX_EXPLOSIONS; inx++)
	{
		if(explosions[inx] != NULL)
		{
			if(explosions[inx]->isDead())
			{
				delete explosions[inx];
				explosions[inx] = NULL;
			}
			else
				explosions[inx]->update();
		}
	}
}

/**
* Renderiza todas las explosiones
*/
void ExplosionManager::render()
{
	for(int inx = 0; inx < MAX_EXPLOSIONS; inx++)
	{
		glLoadIdentity();

		if(explosions[inx] != NULL)
		{
			glDisable(GL_TEXTURE_2D);

			explosions[inx]->render();

			glEnable(GL_TEXTURE_2D);

			glLoadIdentity();
		}
	}
}

/**
* Resetea el administrador de explosiones eliminando cada una de ellas
*/
void ExplosionManager::reset()
{
	for(int inx = 0; inx < MAX_EXPLOSIONS; inx++)
	{
		if(explosions[inx] != NULL)
		{
			delete explosions[inx];
			explosions[inx] = NULL;
		}
	}
}