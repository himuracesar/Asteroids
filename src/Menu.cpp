#include "Menu.h"

/**
* Constructor de la clase Menu
* @param regulateKey Indica si debe regular el teclazo principal. Esto es para que se
* pausada la pantalla del menu una vez que es invocada desde otro game state
*/
Menu::Menu(bool regulateKey)
{
	fontOptions = new Font("fonts/Advert-Regular.ttf", 45);
	fontHS = new Font("fonts/Advert-Regular.ttf", 30);

	ENTER = regulateKey;
	ENTER_OLD = regulateKey;

	option = 0;

	init();
}

/**
* Destructor de la clase Menu
*/
Menu::~Menu()
{
	delete fontOptions;
	delete fontHS;

	Mix_HaltMusic();

	Mix_FreeMusic(music);
	Mix_FreeChunk(menuMove);
	Mix_FreeChunk(menuSelect);
}

/**
* Inicializa los recursos del Menu del juego
*/
void Menu::init()
{
	Game::init();

	setBackground("images/Portada_Asteroids.png");

	setGameState(Game::MENU);
	setGameStateOld(Game::MENU);

	UP = false;
	UP_OLD = false;
	DOWN = false;
	DOWN_OLD = false;

	sHighScore = "High-Score: ";

	itoa(CheckCollision::getHighScore(), highScore, 10);

	sHighScore = sHighScore + highScore;

	music = Mix_LoadMUS("sounds/menu.ogg");

	Mix_PlayMusic(music, -1);

	menuMove = Mix_LoadWAV("sounds/MenuMove.wav");
	menuSelect = Mix_LoadWAV("sounds/MenuSelect.wav");
}

/**
* Actualiza la logica de la pantalla del Menu
*/
void Menu::update(SDL_Event event)
{
	//Game::update(event);

	if(event.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch(event.key.keysym.sym)
		{
			case SDLK_UP:
				UP = true;
				UP_OLD = true;
			break;

			case SDLK_DOWN:
				DOWN = true;
				DOWN_OLD = true;
			break;

			case SDLK_RETURN:
				ENTER = true;
			break;
		}
	}//if event
	else
		if(event.type == SDL_KEYUP)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
					UP = false;
				break;

				case SDLK_DOWN:
					DOWN = false;
				break;
				case SDLK_RETURN:
					ENTER = false;
					ENTER_OLD = false;
				break;
			}
		}

	if(!UP && UP_OLD)
	{
		Mix_PlayChannel(-1, menuMove, 0);

		UP_OLD = false;

		if(option-1 < 0)
			option = NUM_OPTIONS;
		else
			option--;
	}
	else
		if(!DOWN && DOWN_OLD)
		{
			Mix_PlayChannel(-1, menuMove, 0);

			DOWN_OLD = false;

			if(option+1 > NUM_OPTIONS)
				option = 0;
			else
				option++;
		}

	if(ENTER && !ENTER_OLD)
	{
		Mix_PlayChannel(-1, menuSelect, 0);

		SDL_Delay(1000);

		switch(option)
		{
			case 0:
				setGameState(Game::GAME_PLAY);
			break;
			case 1:
				setGameState(Game::INSTRUCTIONS);
			break;
			case 2:
				setGameState(Game::CREDITS);
			break;
			case 3:
				setGameState(Game::EXIT);
			break;
		}
	}
}

/**
* Pinta todos los objetos en el Menu
*/
void Menu::render()
{
	Game::render();

	//strncat(text, highScore, 10);
	//sprintf(textHS, "%s", highScore);

	fontHS->drawString((char*)sHighScore.c_str(), Font::RIGHT, 1, Font::RED);

	if(option == 0)
		fontOptions->drawString("Play", Font::CENTER, 370, Font::YELLOW);
	else
		fontOptions->drawString("Play", Font::CENTER, 370, Font::WHITE);

	if(option == 1)
		fontOptions->drawString("Instructions", Font::CENTER, 420, Font::YELLOW);
	else
		fontOptions->drawString("Instructions", Font::CENTER, 420, Font::WHITE);

	if(option == 2)
		fontOptions->drawString("Credits", Font::CENTER, 470, Font::YELLOW);
	else
		fontOptions->drawString("Credits", Font::CENTER, 470, Font::WHITE);

	if(option == 3)
		fontOptions->drawString("Exit", Font::CENTER, 520, Font::YELLOW);
	else
		fontOptions->drawString("Exit", Font::CENTER, 520, Font::WHITE);
}