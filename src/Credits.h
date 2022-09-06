#ifndef CREDITS_H
    #define CREDITS_H

#include <vector>

#include "Game.h"
#include "ParserXMLCredits.h"
#include "Font.h"
#include "Sprite.h"
#include "Timer.h"

#include "SDL.h"

using namespace std;

/**
* Muestra los creditos del juego
* @author Cesar Himura
*/
class Credits : public Game
{
    private:
        bool ENTER, ENTER_OLD;

        int y;
        int yAux;

        float FADING;

        ParserXMLCredits *parser;

        Font *fontTG;
        Font *fontMG;
        Sprite *logo_spr;
        Timer *timer;

        typedef pair<string, string> sCredits;

        vector<sCredits> vCredits;

        vector<sCredits>::iterator iter;

        /** FUNCIONES **/
        void fadingSprite();

    public:
		Credits();
		~Credits();
		virtual void init();
		virtual void update(SDL_Event event);
		virtual void render();
};

#endif // CREDITS_H
