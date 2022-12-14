#include "GamePlay.h"

/**
* Constructor de la clase GamePlay
*/
GamePlay::GamePlay()
{
	player = new Player("images/nave_74x115.png");
	fontScore = new Font("fonts/juliet.ttf", 20);
	fontPause = new Font("fonts/juliet.ttf", 40);
	//turbine = new Turbine(200,200);

	init();
}

/**
* Destructor de la clase GamePlay
*/
GamePlay::~GamePlay()
{
	delete player;
	delete fontScore;
	delete fontPause;
	//delete turbine;
	
	AsteroidManager::reset();
	CheckCollision::reset();
	ExplosionManager::reset();
	
	glDeleteTextures(1, &life_texture);

	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_FreeChunk(shot);
	Mix_FreeChunk(explosionSound);
}

/**
* Inicializa los recursos del juego
*/
void GamePlay::init()
{
	Game::init();

	setBackground("images/bg.jpg");

	setGameState(Game::GAME_PLAY);
	setGameStateOld(Game::GAME_PLAY);

	gs = GamePlay::GAME_PLAY;

	CheckCollision::setScore(0);

	srand(time(0));

	initPlayer();

	LEFT = false;
	RIGHT = false;
	UP = UP_OLD = false;
	DOWN = DOWN_OLD = false;
	FIRE = false;
	FIRE_OLD = false;
	P = false;
	P_OLD = false;

	loadTexture(&life_texture, "images/nave_74x115.png");

	player->setWidth(51);
	player->setHeight(80);

	GenerateIconLife();

	createAsteroids();

	ciclos = 0;
	explosionsPlayer = 0;

	//turbine->setAngle(0);

	music = Mix_LoadMUS("sounds/music1.mid");

	Mix_PlayMusic(music, -1);

	Mix_VolumeMusic(70);

	shot = Mix_LoadWAV("sounds/laser_gun_shot.wav");
	explosionSound = Mix_LoadWAV("sounds/bomb_explosion.wav");
}

/**
* Inicializa los recursos del jugador, posicion, velocidad, vidas, angulo de rotacion
*/
void GamePlay::initPlayer()
{
	player->setX(WIDTH_SCREEN/2 + player->getWidth()/2);
	player->setY(HEIGHT_SCREEN/2 - player->getHeight()/2);
	player->setAngle(rand() % 360);
	player->setVx(0);
	player->setVy(0);
	player->setLife(3);
}

/**
* Gestiona que logica del juego actualizar
* @param event Es el evento que debera ser actualizado
*/
void GamePlay::update(SDL_Event event)
{
	switch(gs)
	{
		case GamePlay::GAME_PLAY:
			updateGamePlay(event);
		break;
		case GamePlay::PAUSE:
			updatePause(event);
		break;
		case GamePlay::GAME_OVER:
			updateGameOver(event);
		break;
	}
}

/**
* Actualiza la logica del juego (gameState interno = GAME_PLAY)
* @param event Es el evento que debera ser actualizado
*/
void GamePlay::updateGamePlay(SDL_Event event)
{
	//Game::update(event);

	ciclos++;
	
	//If a key was pressed
	if(event.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch(event.key.keysym.sym)
		{
			case SDLK_LEFT:
				LEFT = true;
			break;
			case SDLK_RIGHT:
				RIGHT = true;
			break;
			case SDLK_UP:
				UP = true;
			break;
			case SDLK_DOWN:
				DOWN = true;
			break;
			case SDLK_SPACE:
				FIRE = true;
				FIRE_OLD = true;
			break;
			case SDLK_p:
				P = true;
				P_OLD = true;
			break;
		}
	}
	//If a key was released
	else 
		if(event.type == SDL_KEYUP)
		{
			//Adjust the velocity
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:
					LEFT = false;
				break;
				case SDLK_RIGHT:
					RIGHT = false;
				break;
				case SDLK_UP:
					UP = false;
				break;
				case SDLK_DOWN:
					DOWN = false;
				break;
				case SDLK_SPACE:
					FIRE = false;
				break;
				case SDLK_p:
					P = false;
			}
		}
	
	if(player->getState() == Player::LIVE)
	{
		if(LEFT == true){
			player->setAngle(player->getAngle() - Player::SPEED_ROTATE);

			if(player->getAngle() < 0)
				player->setAngle(360 - Player::SPEED_ROTATE);
		}
		else 
			if(RIGHT == true){
				player->setAngle(player->getAngle() + Player::SPEED_ROTATE);

				if(player->getAngle() > 359)
					player->setAngle(0);
			}
			else
				if(UP && abs(player->getVy()) < Player::MAX_SPEED && abs(player->getVx()) < Player::MAX_SPEED)
				{
					player->setVx(player->getVx()+(Player::ACCEL/2.0 * cosf(DegreeToRad(player->getAngleReal()))));
					player->setVy(player->getVy()+(Player::ACCEL/2.0 * sinf(DegreeToRad(player->getAngleReal()))));

					if(abs(player->getVx()) > Player::MAX_SPEED)
						player->setVx(Player::MAX_SPEED * (player->getVx()/abs(player->getVx())));

					if(abs(player->getVy()) > Player::MAX_SPEED)
						player->setVy(Player::MAX_SPEED * (player->getVy()/abs(player->getVy())));

				}//if UP
				else
					if(DOWN)
					{
						if(player->getVx() != 0)
							if(player->getVx() > 0)
								if(player->getVx()-1 < 0)
									player->setVx(0);
								else
									player->setVx(player->getVx()-1);
							else
								if(player->getVx()+1 > 0)
									player->setVx(0);
								else
									player->setVx(player->getVx()+1);
								
						if(player->getVy() != 0)
							if(player->getVy() > 0)
								if(player->getVy()-1 < 0)
									player->setVy(0);
								else
									player->setVy(player->getVy()-1);
							else
								if(player->getVy()+1 > 0)
									player->setVy(0);
								else
									player->setVy(player->getVy()+1);
					}//if DOWN
	
		if(!FIRE && FIRE_OLD)
		{
			FIRE_OLD = false;
			player->fire();

			//explosion = new Explosion(rand()%800/1.0+1,rand()%600/1.0+1);

			Mix_PlayChannel(-1, shot, 0);
		}
		else
			if(!P && P_OLD)
			{
				P_OLD = false;
				gs = GamePlay::PAUSE;
				optionPause = GamePlay::PAUSE_CONTINUE;
				Mix_Pause(-1);
				Mix_PauseMusic();
			}
	}//if(player->getState() == Player::LIVE)
	
	if(CheckCollision::check())
		Mix_PlayChannel(-1, explosionSound, 0);

	player->update();
	
	if(gs != GamePlay::PAUSE)
	{
		for(int index = 0; index < AsteroidManager::MAX_ASTEROIDS; index++)
		{
			if(AsteroidManager::getAsteroid(index) != NULL)
			{
				AsteroidManager::getAsteroid(index)->update();
			}
		}
	}

	glLoadIdentity();

	if(ciclos == 100)
	{
		createAsteroids();
		ciclos = 0;
	}

	//****** CORRE EN WINDOWS *******
	itoa(CheckCollision::getScore(), score, 10);
	//****** CORRE EN LINUX *******
	//sprintf(score, "%d", CheckCollision::getScore());

	if(player->getLifes() < 0)
	{
		gs = GamePlay::GAME_OVER;

		if(CheckCollision::getHighScore() < CheckCollision::getScore())
			CheckCollision::setHighScore(CheckCollision::getScore());
	}

	if(player->getLife() < 0)
	{
		player->setState(Player::EXPLODE);

		if(explosionsPlayer < ExplosionManager::MAX_EXPLOSIONS*4)
			explosionsPlayer++;

		if(ExplosionManager::getSpaces() > 0 && explosionsPlayer < ExplosionManager::MAX_EXPLOSIONS*4)
		{
			player->setState(Player::EXPLODE);

			player->setVx(0);
			player->setVy(0);

			if(explosionsPlayer % 2 == 0)
				ExplosionManager::addExplosion(new Explosion(rand() % player->getHeight() - player->getX(),
															 rand() % player->getHeight() - player->getY()));
			else
				ExplosionManager::addExplosion(new Explosion(rand() % player->getHeight() + player->getX(),
															 rand() % player->getHeight() + player->getY()));

			Mix_PlayChannel(-1, explosionSound, 0);
		}

		if(ExplosionManager::getSpaces() == ExplosionManager::MAX_EXPLOSIONS)
		{
			player->setLifes(player->getLifes()-1);

			if(player->getLifes() >= 0)
			{
				initPlayer();
				player->setState(Player::LIVE);
				explosionsPlayer = 0;
			}
		}
	}

	ExplosionManager::update();

	/*turbine->setAngle(player->getAngleReal()+180);
    turbine->setX(player->getX()+(player->getHeight()/2)*cosf(DegreeToRad(turbine->getAngle())));
    turbine->setY(player->getY()+(player->getHeight()/2)*sinf(DegreeToRad(turbine->getAngle())));
	turbine->setGravityX(2.0f*cosf(DegreeToRad(turbine->getAngle())));
    turbine->setGravityY(2.0f*sinf(DegreeToRad(turbine->getAngle())));*/
	//turbine->update();
}

/**
* Actualiza la logica cuando el juego esta pausado
* @param event Es el evento que debera ser actualizado
*/
void GamePlay::updatePause(SDL_Event event)
{
	if(event.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch(event.key.keysym.sym)
		{
			case SDLK_p:
				P = true;
				P_OLD = true;
			break;
			case SDLK_UP:
				UP = true;
				UP_OLD = true;
			break;
			case SDLK_DOWN:
				DOWN = true;
				DOWN_OLD = true;
			break;
			case SDLK_RETURN:
				if(optionPause == GamePlay::PAUSE_CONTINUE)
				{
					gs = GamePlay::GAME_PLAY;
				}
				else
				{
					setGameState(Game::MENU);
					setRegulateKey(true);
				}
			break;
		}
	}
	else
		if(event.type == SDL_KEYUP)
		{
			//Adjust the velocity
			switch(event.key.keysym.sym)
			{
				case SDLK_p:
					P = false;
				break;
				case SDLK_UP:
					UP = false;
				break;
				case SDLK_DOWN:
					DOWN = false;
				break;
			}
		}

	if(!P && P_OLD)
	{
		P_OLD = false;
		gs = GamePlay::GAME_PLAY;
		Mix_Resume(-1);
		Mix_ResumeMusic();
	}
	else
		if(!UP && UP_OLD)
		{
			optionPause = (optionPause == GamePlay::PAUSE_CONTINUE) ? GamePlay::PAUSE_MENU : GamePlay::PAUSE_CONTINUE; 
			UP_OLD = false;
		}
		else
			if(!DOWN && DOWN_OLD)
			{
				optionPause = (optionPause == GamePlay::PAUSE_CONTINUE) ? GamePlay::PAUSE_MENU : GamePlay::PAUSE_CONTINUE; 
				DOWN_OLD = false;
			}
}

/**
* Actualiza la logica del juego cuando se encuentra en estado Game Over
* @param event Es el evento que debera ser actualizado
*/
void GamePlay::updateGameOver(SDL_Event event)
{
	if(event.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:
				setGameState(Game::MENU);
			break;
		}
	}
}


/**
* Gestiona que estado interno debe ser renderizado
*/
void GamePlay::render()
{
	switch(gs)
	{
		case GamePlay::GAME_PLAY:
			renderGamePlay();
		break;
		case GamePlay::PAUSE:
			renderPause();
		break;
		case GamePlay::GAME_OVER:
			renderGameOver();
		break;
	}
}

/**
* Renderiza los objetos del juego
*/
void GamePlay::renderGamePlay()
{
	Game::render();

	glLoadIdentity();

	if(player->getState() == Player::LIVE)
	{
		player->render();
		//turbine->setResetParticles(true);
	}
	else
	{
	    //turbine->setResetParticles(false);
	}

	if(player->getState() == Player::LIVE)
		player->render();

	for(int index = 0; index < AsteroidManager::MAX_ASTEROIDS; index++)
	{
		if(AsteroidManager::getAsteroid(index) != NULL)
		{
			AsteroidManager::getAsteroid(index)->render();
		}
	}

	//*** Indicadores de Vida ***
    for(int inx = 0; inx < player->getLifes(); inx++)
    {
        glLoadIdentity();
		glEnable(GL_BLEND);
        glTranslatef(inx*WIDTH_ICON_LIFE, HEIGHT_SCREEN-HEIGHT_ICON_LIFE, 0);
        glBindTexture(GL_TEXTURE_2D, life_texture);
        glCallList(iconLife);
    }

	glLoadIdentity();

	fontScore->drawString(score, Font::LEFT, 1, Font::WHITE);
	
	glLoadIdentity();

    //turbine->render();

	glLoadIdentity();

	ExplosionManager::render();
}

/**
* Renderiza la pausa del juego
*/
void GamePlay::renderPause()
{
	//Game::render();
	renderGamePlay();

	glLoadIdentity();

	fontPause->drawString("PAUSE", Font::CENTER, 200, Font::WHITE);

	glLoadIdentity();

	if(optionPause == GamePlay::PAUSE_CONTINUE)
	{
		fontScore->drawString("Continue", Font::CENTER, 250, Font::YELLOW);
		fontScore->drawString("Menu", Font::CENTER, 280, Font::WHITE);
	}
	else
	{
		fontScore->drawString("Continue", Font::CENTER, 250, Font::WHITE);
		fontScore->drawString("Menu", Font::CENTER, 280, Font::YELLOW);
	}
}

/**
* Renderiza el estado interno del juego Game Over
*/
void GamePlay::renderGameOver()
{
	//Game::render();
	renderGamePlay();

	fontPause->drawString("GAME OVER", Font::CENTER, 200, Font::WHITE);

	fontScore->drawString("Press ENTER to continue", Font::CENTER, 250, Font::WHITE);
}

/**
* Crea nuevos asteroides
*/
void GamePlay::createAsteroids()
{
	while(0 < AsteroidManager::getSpaces())
	{
		if(AsteroidManager::getSpaces() == 1)
			AsteroidManager::addAsteroid(new Asteroid("images/asteroid.png", Asteroid::MEDIUM));
		else
			AsteroidManager::addAsteroid(new Asteroid("images/asteroid.png", Asteroid::RANDOM));
	}
}

/**
* Genera una lista en OpenGL para generar los indicadores de vida
*/
void GamePlay::GenerateIconLife()
{
	iconLife = glGenLists(1);

	glNewList(iconLife, GL_COMPILE);

	glBegin(GL_QUADS);
        glTexCoord2i(0,0);
        glVertex2i(0, 0);
        glTexCoord2i(0,1);
        glVertex2i(0, HEIGHT_ICON_LIFE);
        glTexCoord2i(1,1);
        glVertex2i(WIDTH_ICON_LIFE,HEIGHT_ICON_LIFE);
        glTexCoord2i(1,0);
        glVertex2i(WIDTH_ICON_LIFE,0);
    glEnd();

	glEndList();
} //GenerateIconLife

/**
* Carga una textura en memoria
* @param texture Es la variable donde almacenara la textura
* @param file Es el archivo de la textura (imagen) a cargar
*/
void GamePlay::loadTexture(GLuint *texture, const char *file)
{
    SDL_Surface *surface = IMG_Load(file); // this surface will tell us the details of the image

	GLint nColors;
	GLenum textureFormat;

    if(surface){
        // Check that the image’s width is a power of 2
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("warning: image.bmp’s width is not a power of 2\n");
        }

        // Also check if the height is a power of 2
        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("warning: image.bmp’s height is not a power of 2\n");
        }

        //get number of channels in the SDL surface
        nColors = surface->format->BytesPerPixel;

        //contains an alpha channel
        if(nColors == 4)
        {
            if(surface->format->Rmask==0x000000ff)
                textureFormat = GL_RGBA;
            else
                textureFormat = GL_BGRA;
        }
        else if(nColors == 3) //no alpha channel
        {
            if(surface->format->Rmask==0x000000ff)
                textureFormat = GL_RGB;
            else
                textureFormat = GL_BGR;
        }
        else
        {
            printf("warning: the image is not truecolor…this will break ");
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures(1, texture);

        // Bind the texture object
        glBindTexture(GL_TEXTURE_2D, *texture);

        // Set the texture’s stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D( GL_TEXTURE_2D, 0, nColors, surface->w, surface->h, 0,
        textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

        //glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_DECAL);
    }
    else {
        printf("SDL could not load %s: %s\n", file, SDL_GetError());
        SDL_Quit();
    }

    // Free the SDL_Surface only if it was successfully created
    if(surface) {
        SDL_FreeSurface(surface);
    }
}