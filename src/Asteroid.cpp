#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iostream>

#include "CheckCollision.h"
#include "AsteroidManager.h"

#define SPEED_ROTATE 0.5
#define SPEED_TRASLATION 2.5
#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600
#define MAX_DISTANCE 600
#define DegreeToRad(n) n*0.017453292519943295769236907684886
#define RadToDegree(n) n*57.295779513082320876798154814105

/**
* Crea un asteroide
* @param file Archivo de donde cargara la textura (imagen)
* @param type Tipo de Asteroide que creara: Grande, Mediano o Pequenio. Al mandar
* RANDOM el tipo de asteroide sera aleatorio
*/
Asteroid::Asteroid(char *file, int type):
	Sprite(file)
{
		setWidth(100);	
		setHeight(91);

		angle_dir = rand() % 359;

		double xa, ya;

		//Cuadrante I -- III
		if(angle_dir > 0 && angle_dir < 90)
		{
			this->setX(rand() % WIDTH_SCREEN/2);
			this->setY(rand() % HEIGHT_SCREEN + HEIGHT_SCREEN/2);
			
			xa = MAX_DISTANCE * cosf(DegreeToRad(this->getAngleDirection()));
			ya = MAX_DISTANCE * sinf(DegreeToRad(this->getAngleDirection()));

			this->setX(this->getX() - xa);
			this->setY(this->getY() + ya);
		}
		else
			if(angle_dir > 90 && angle_dir < 180)//Cuadrante II -- IV
			{
				this->setX(rand() % WIDTH_SCREEN + WIDTH_SCREEN/2);
				this->setY(rand() % HEIGHT_SCREEN + HEIGHT_SCREEN/2);

				xa = MAX_DISTANCE * cosf(DegreeToRad(this->getAngleDirection()));
				ya = MAX_DISTANCE * sinf(DegreeToRad(this->getAngleDirection()));

				this->setX(this->getX() + xa);
				this->setY(this->getY() + ya);
			}
			else
				if(angle_dir > 180 && angle_dir < 270)//Cuadrante III -- I
				{
					this->setX(rand() % WIDTH_SCREEN + WIDTH_SCREEN/2);
					this->setY(rand() % HEIGHT_SCREEN/2);

					xa = MAX_DISTANCE * cosf(DegreeToRad(this->getAngleDirection()));
					ya = MAX_DISTANCE * sinf(DegreeToRad(this->getAngleDirection()));

					this->setX(this->getX() + xa);
					this->setY(this->getY() - ya);
				}
				else
					if(angle_dir > 270 && angle_dir < 360)//Cuadrante IV -- II
					{
						this->setX(rand() % WIDTH_SCREEN/2);
						this->setY(rand() % HEIGHT_SCREEN/2);

						xa = MAX_DISTANCE * cosf(DegreeToRad(this->getAngleDirection()));
						ya = MAX_DISTANCE * sinf(DegreeToRad(this->getAngleDirection()));

						this->setX(this->getX() - xa);
						this->setY(this->getY() - ya);
					}

		this->setAngle(0);

		this->setVx(SPEED_TRASLATION * cosf(DegreeToRad(this->getAngleDirection())));
		this->setVy(SPEED_TRASLATION * sinf(DegreeToRad(this->getAngleDirection())));

		CheckCollision::addSprite(this, CheckCollision::ENEMY);

		this->setName("Asteroid");
		this->type = type;

		if(type == RANDOM)
		{
			this->type = rand() % 3 + 1;
		}

		switch(this->type)
		{
			case MEDIUM:
				this->setWidth(this->getWidth()/2);
				this->setHeight(this->getHeight()/2);
			break;

			case LITTLE:
				this->setWidth(this->getWidth()/4);
				this->setHeight(this->getHeight()/4);
			break;
		}
}

/**
* Crea un asteroide
* @param file Archivo de donde cargara la textura (imagen)
* @param type Tipo de Asteroide que creara: Grande, Mediano o Pequenio. Al mandar
* RANDOM el tipo de asteroide sera aleatorio
* @param x Coordenada en x del asteroide a crear
* @param y Coordenada en y del asteroide a crear
* @param vx Velocidad en x del asteroide a crear
* @param vy Coordenada en y del asteroide a crear
* @param angleDir Angulo de direccion del asteroide a crear
*/
Asteroid::Asteroid(char *file, int type, double x, double y, double vx, double vy, double angleDir):
	Sprite(file)
{
	this->setX(x);
	this->setY(y);
	this->setVx(vx);
	this->setVy(vy);
	this->setAngleDirection(0);
	this->setName("Asteroid");
	this->setType(type);
	this->setAngle(0);

	switch(this->type)
	{
		case MEDIUM:
			this->setWidth(this->getWidth()/2);
			this->setHeight(this->getHeight()/2);
		break;

		case LITTLE:
			this->setWidth(this->getWidth()/4);
			this->setHeight(this->getHeight()/4);
		break;
	}

	CheckCollision::addSprite(this, CheckCollision::ENEMY);
}

/**
* Destructor de la clase Asteroide
*/
Asteroid::~Asteroid()
{}

/**
* Actualiza la logica de un asteroide
*/
void Asteroid::update()
{
	this->setAngle(SPEED_ROTATE + this->getAngle()); 
	this->setX(this->getX() + this->getVx());
	this->setY(this->getY() + this->getVy());

	if(this->getAngle() > 359)
		this->setAngle(0);

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

	Sprite::update();
}

/**
* Gestiona la colision de un asteroide
*/
void Asteroid::OnCollide()
{
	double xa, ya;

	switch(this->getType())
	{
		case BIG:
			this->setWidth(this->getWidth()/2);
			this->setHeight(this->getHeight()/2);

			this->type = MEDIUM;
		break;

		case MEDIUM:
			this->setWidth(this->getWidth()/2);
			this->setHeight(this->getHeight()/2);

			this->type = LITTLE;
		break;

		case LITTLE:
			AsteroidManager::destroyAsteroid(this->getID());

			this->type = DESTROY;
		break;
	}
}