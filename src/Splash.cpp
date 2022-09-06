#include "Splash.h"

/**
* Constructor de la clase Splash (ventana de presentacion)
*/
Splash::Splash()
{
    logo_spr = new Sprite("images/Himura_Productions_presents_180.jpg");
    font = new Font("fonts/BlackCastleMF.ttf", 65);
    timer = new Timer(3700);

    init();
}

/**
* Destructor de la clase Splash
*/
Splash::~Splash()
{
    delete logo_spr;
    delete timer;
    delete font;
}

/**
* Inicializa los recursos del Splash
*/
void Splash::init()
{
    Game::init();

	//setBackground("images/Portada_Arkanoid.png");

	setGameState(Game::SPLASH);
	setGameStateOld(Game::SPLASH);

	logo_spr->setWidth(330);
	logo_spr->setHeight(430);
	logo_spr->setFade(0.0f);
	logo_spr->setAngle(180);
	font->setFade(0.0f);

	screen = 1;
	FADING = 0.003000f;
}

/**
* Actualiza la logica del Splash
*/
void Splash::update(SDL_Event event)
{
    //printf("startTicks:: %d\n", timer->get_ticks());

    if(event.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:

			break;

			default:
			break;
		}
	}//if event
	else
		if(event.type == SDL_KEYUP)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_RETURN:
					setRegulateKey(false);
					setGameState(Game::MENU);
				break;

				default:
				break;
			}
		}

    switch(screen)
    {
        case 1:
            fadingFont();
        break;

        case 2:
            fadingSprite();
        break;

        case 3:
            fadingFont();
        break;
    }

    if(screen > SCREENS)
	{
        setGameState(Game::MENU);
		setRegulateKey(false);
	}
}

/**
* Renderea el Splash
*/
void Splash::render()
{
	Game::render();

    switch(screen)
    {
        case 1:
            font->drawString("RomaComputer", Font::CENTER, HEIGHT_SCREEN/2 - font->getHeight()/2, Font::WHITE);
        break;

        case 2:
            logo_spr->render();
        break;

        case 3:
            font->drawString("a Cesar Himura game", Font::CENTER, HEIGHT_SCREEN/2 - font->getHeight()/2, Font::WHITE);
        break;
    }

	glLoadIdentity();
}

/**
* Crea el efecto fading completo para Fuentes (texto)
*/
void Splash::fadingFont()
{
    font->setFade(font->getFade() + Splash::FADING);
    if(font->getFade() >= 1.0f)
    {
        font->setFade(1.0f);

        if(!timer->is_started())
            timer->start();

        if(timer->is_time())
        {
            FADING = -FADING;
            timer->stop();
        }
    }
    else
        if(font->getFade() <= 0.0f)
        {
            screen++;
            font->setFade(0.0f);
            FADING = -FADING;
        }
}

/**
* Crea el efecto fading completo para Sprites (imagenes)
*/
void Splash::fadingSprite()
{
    logo_spr->setFade(logo_spr->getFade() + Splash::FADING);
    if(logo_spr->getFade() >= 1.0f)
    {
        logo_spr->setFade(1.0f);

        if(!timer->is_started())
            timer->start();

        if(timer->is_time())
        {
            timer->stop();
            FADING = -FADING;
        }
    }
    else
        if(logo_spr->getFade() <= 0.0f)
        {
            screen++;
            logo_spr->setFade(0.0f);
            FADING = -FADING;
        }

    logo_spr->setX(WIDTH_SCREEN/2);
    logo_spr->setY(HEIGHT_SCREEN/2);
    logo_spr->update();
}
