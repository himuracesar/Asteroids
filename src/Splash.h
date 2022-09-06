#ifndef SPLASH_H
    #define SPLASH_H

#include "Game.h"
#include "Sprite.h"
#include "Font.h"
#include "Timer.h"
#include "Menu.h"

#include "SDL.h"

/**
* Clase Splash para la presentacion del juego
* @author Cesar Himura
*/
class Splash : public Game
{
    private:
        GLuint image;
        GLuint logo;
        GLenum texture_format;
		GLint nofcolors;

		float FADING;

		const static int SCREENS = 3;

		int screen;

        Sprite *logo_spr;
        Font *font;
        Timer *timer;

        /** FUNCIONES **/
        void fadingFont();
        void fadingSprite();

    public:
        Splash();
		virtual ~Splash();
		virtual void init();
		virtual void update(SDL_Event event);
		virtual void render();
};

#endif // SPLASH_H
