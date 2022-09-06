#include <iostream>

#include "Player.h"
#include "CheckCollision.h"

/**
* Constructor de la clase Shot, tiene el contructor del padre como default
* @param file Archivo de donde cargara la textura (imagen)
*/
Shot::Shot(char *file):
	Sprite(file)
{
	this->setName("Shot");

	CheckCollision::addSprite(this, CheckCollision::ALLY);
}

/**
* Destructor de la clase Shot
*/
Shot::~Shot()
{
}

/*
* Actualiza la logica del disparo
**/
void Shot::update()
{
	this->setX(this->getX() + this->getVx());
	this->setY(this->getY() + this->getVy());
	setWidth(8);
	setHeight(25);

	Sprite::update();
}

/**
* Metodo que gestiona la colision de un disparo
*/
void Shot::OnCollide()
{
	for(int inx = 0; inx < CheckCollision::MAX_ALLY; inx++)
	{
		if((CheckCollision::getSprite(inx, CheckCollision::ALLY)) != NULL)
		{
			if((CheckCollision::getSprite(inx, CheckCollision::ALLY))->getName() == "Player")
			{
				((Player*)(CheckCollision::getSprite(inx, CheckCollision::ALLY)))->destroyShot(this->getId());
				break;
			}
		}//if sprite != NULL
	}
}