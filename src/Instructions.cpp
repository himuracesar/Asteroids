#include "Instructions.h"

/**
* Constructor de la clase Instructions
*/
Instructions::Instructions()
{
	font = new Font("fonts/Advert-Regular.ttf", 35);
	fontTitle = new Font("fonts/Advert-Regular.ttf", 60);

	init();
}

/**
* Destructor de la clase Instructions
*/
Instructions::~Instructions()
{
	delete font;
	delete fontTitle;
}

/**
* Inicializa los recursos de la pantalla de Instrucciones
*/
void Instructions::init()
{
	Game::init();

	//setBackground("images/Portada_Asteroids.png");

	setGameState(Game::INSTRUCTIONS);
	setGameStateOld(Game::INSTRUCTIONS);

	ENTER = true;
	ENTER_OLD = true;
}

/**
* Actualiza la logica de la pantalla de instrucciones
*/
void Instructions::update(SDL_Event event)
{
	Game::update(event);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_RETURN)
			ENTER = true;
	}
	else
	{
		ENTER = false;
		ENTER_OLD = false;
	}

	if(ENTER && !ENTER_OLD)
		setGameState(Game::MENU	);

	//render();
}

/**
* Dibuja todos los objetos en la pantalla de instrucciones
*/
void Instructions::render()
{
	//Game::render();

	fontTitle->drawString("INSTRUCTIONS", Font::CENTER, 0, Font::WHITE);

	font->drawString("Use the keyboard to move the ship.", Font::LEFT, 60, Font::WHITE);
	font->drawString("ARROW_LEFT: Rotate the ship to the left.", Font::LEFT, 100, Font::WHITE);
	font->drawString("ARROW_RIGHT: Rotate the ship to the right.", Font::LEFT, 140, Font::WHITE);
	font->drawString("ARROW_UP: Accelerate the ship.", Font::LEFT, 180, Font::WHITE);
	font->drawString("ARROW_DOWN: Stop the ship.", Font::LEFT, 220, Font::WHITE);
	font->drawString("SPACE_BAR: Fire.", Font::LEFT, 260, Font::WHITE);
	font->drawString("P: Pause the game.", Font::LEFT, 300, Font::WHITE);
	font->drawString("ESC: Exit the game.", Font::LEFT, 340, Font::WHITE);
	font->drawString("You are the last hope for the Earth", Font::CENTER, 390, Font::WHITE);
	font->drawString("GOOD LUCK!!!", Font::CENTER, 430, Font::WHITE);
	font->drawString("Press ENTER to exit", Font::CENTER, 540, Font::YELLOW);
}