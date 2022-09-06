#ifndef INSTRUCTIONS_H
	#define INSTRUCTIONS_H

#include "Game.h"
#include "Font.h"

class Instructions : public Game
{
	private:
		Font *font;
		Font *fontTitle;
		bool ENTER;
		bool ENTER_OLD;

	public:
		Instructions();
		~Instructions();
		virtual void init();
		virtual void update(SDL_Event event);
		virtual void render();
};

#endif;