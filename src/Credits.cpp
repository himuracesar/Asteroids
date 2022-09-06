#include "Credits.h"

/**
* Constructor de la clase Credits, crea el parseador del XML y crea las fuentes
*/
Credits::Credits()
{
    parser = new ParserXMLCredits();

    fontTG = new Font((char*)parser->getFont().c_str(), parser->getSizeTitleGroup());
    fontMG = new Font((char*)parser->getFont().c_str(), parser->getSizeMemberGroup());

    logo_spr = new Sprite("images/Himura_Productions_credits.jpg");

    timer = new Timer(3600);

    init();
}

/**
* Destruye los objetos que estan en memoria (heap)
*/
Credits::~Credits()
{
    delete parser;
    delete fontTG;
    delete fontMG;
    delete timer;
}

/**
* Inicializa los recursos de este gameState
*/
void Credits::init()
{
    Game::init();

    setGameState(Game::CREDITS);
	setGameStateOld(Game::CREDITS);

	ENTER = ENTER_OLD = true;

	logo_spr->setFade(0.0f);
	logo_spr->setWidth(300);
	logo_spr->setHeight(430);
	logo_spr->setAngle(180);

	y = 600;//Game::HEIGHT_SCREEN + 5;

	vCredits = parser->getCredits();

	FADING = 0.003000f;
}

/**
* Actualiza la logica del game state Credits
* @param event Es el evento de SDL
*/
void Credits::update(SDL_Event event)
{
    Game::update(event);

    if(event.type == SDL_KEYDOWN)
	{
	    switch(event.key.keysym.sym)
        {
            case SDLK_RETURN:
                ENTER = true;
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
					ENTER = false;
					ENTER_OLD = false;
				break;

				default:
				break;
			}
		}

	if(ENTER && !ENTER_OLD)
	{
	    ENTER_OLD = false;
        setGameState(Game::MENU);
	}

	y -= 2;
}

/**
* Dibuja los creditos en pantalla
*/
void Credits::render()
{
    yAux = y;

    for(iter = vCredits.begin(); iter < vCredits.end(); ++iter)
    {
        if(iter->first == "TG")
        {
            yAux += 73;
            if(yAux > -30 && yAux < 605)
                fontTG->drawString((char*)iter->second.c_str(), Font::CENTER, yAux, Font::WHITE);
        }
        else
        {
            yAux += 29;
            if(yAux > -25 && yAux < 605)
                fontMG->drawString((char*)iter->second.c_str(), Font::CENTER, yAux, Font::WHITE);
        }
    }

    if(yAux < -80)
    {
        //setGameState(Game::MENU);
        fadingSprite();
        logo_spr->render();
    }
}

/**
* Crea el efecto fading completo para Sprites (imagenes)
*/
void Credits::fadingSprite()
{
    logo_spr->setFade(logo_spr->getFade() + Credits::FADING);
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
        if(logo_spr->getFade() <= -0.15f)
        {
            setGameState(Game::MENU);
            logo_spr->setFade(0.0f);
            FADING = -FADING;
        }

    logo_spr->setX(WIDTH_SCREEN/2);
    logo_spr->setY(HEIGHT_SCREEN/2);
    logo_spr->update();
}
