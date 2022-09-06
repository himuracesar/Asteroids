#include <math.h>
#include <stdio.h>
#include <iostream>

#include "Player.h"
#include "CheckCollision.h"

#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600

#define DegreeToRad(n) n*0.017453292519943295769236907684886
#define RadToDegree(n) n*57.295779513082320876798154814105

/**
* Constructor de la Nave (default - el del padre), agrega la nave al equipo de colisiones al
* que pertence
* @param file Es un puntero a char que contiene el nombre del archivo (textura) de la nave
*/
Player::Player(char *file):
	Sprite(file)
{
	for(int index = 0; index < MAX_SHOTS; index++)
	{
		shots[index] = NULL;
	}

	this->setName("Player");

	CheckCollision::addSprite(this, CheckCollision::ALLY);

	idShot = 0;
	lifes = 4;
	life = 3;//Son 3 puntos de vida
	state = LIVE;
}

/**
* Destructor de Player, libera los recursos ocupados
*/
Player::~Player()
{
	for(int inx = 0; inx < MAX_SHOTS; inx++)
	{
		delete shots[inx];

		shots[inx] = NULL;
	}
}

/*
* Actualiza la logica del player
**/
void Player::update()
{
	this->setX(this->getX() + this->getVx());
	this->setY(this->getY() + this->getVy());

	if(this->getX() > WIDTH_SCREEN + 10)
		this->setX(0);
	else
		if(this->getX() < -10)
			this->setX(WIDTH_SCREEN); 

	if(this->getY() > HEIGHT_SCREEN + 10)
		this->setY(0);
	else
		if(this->getY() < -10)
			this->setY(HEIGHT_SCREEN);

	//*** Actualiza los disparos ***
	for(int inx = 0; inx < MAX_SHOTS; inx++)
	{
		if(shots[inx] != NULL)
		{
			shots[inx]->update();

			if(shots[inx]->getX() > WIDTH_SCREEN + 10 || shots[inx]->getX() < -10 ||
			   shots[inx]->getY() > HEIGHT_SCREEN + 10 || shots[inx]->getY() < -10)
			{
				CheckCollision::deleteSprite(shots[inx]->getId(), CheckCollision::ALLY);

				delete shots[inx];

				shots[inx] = NULL;
			}
		}
	}//for

	Sprite::update();
}

/**
* La nave realiza un disparo
*/
void Player::fire()
{
	for(int inx = 0; inx < MAX_SHOTS; inx++)
	{
		if(shots[inx] == NULL)
		{
			shots[inx] = new Shot("images/Bala.png");
			shots[inx]->setAngle(this->getAngle());
			shots[inx]->setX(this->getX());
			shots[inx]->setY(this->getY());
			shots[inx]->setVx(Shot::MAX_SPEED * cosf(DegreeToRad(shots[inx]->getAngleReal())));
			shots[inx]->setVy(Shot::MAX_SPEED * sinf(DegreeToRad(shots[inx]->getAngleReal())));
			shots[inx]->setId(idShot++);

			break;
		}
	}
}

/**
* Destruye un disparo de la nave (por ej. al salir de la pantalla o al hacer colision
* con un asteroide)
* @param id Es el ID del disparo a destruir
*/
void Player::destroyShot(int id)
{
	for(int index = 0; index < MAX_SHOTS; index++)
	{
		if(shots[index] != NULL)
		{
			if(shots[index]->getId() == id)
			{
				delete shots[index];
				shots[index] = NULL;

				break;
			}
		}
	}
}

/**
* Realiza las instrucciones necesarias cuando la nave ha colisionado con un asteroide
* @param type Tipo de Asteroide con el que colisiona
*/
void Player::OnCollide(int type)
{
	//std::cout << "Se estrello la nave PLAYER" << std::endl;
	switch(type)
	{
		case Asteroid::BIG:
			life -= 3;
		break;
		case Asteroid::MEDIUM:
			life -= 2;
		break;
		case Asteroid::LITTLE:
			life--;
		break;
	}
}

/**
* Dibuja al player en pantalla
*/
void Player::render()
{
	for(int inx = 0; inx < MAX_SHOTS; inx++)
	{
		if(shots[inx] != NULL)
		{
			shots[inx]->render();
		}
	}

	Sprite::render();
}