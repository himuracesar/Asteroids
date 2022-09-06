#ifndef FONT_H
    #define FONT_H

#include<math.h>

#include "SDL_ttf.h"
#include "SDL_opengl.h"
#include "SDL.h"

#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600

/**
* Clase para pintar cadenas en pantalla con diferentes fuentes
* @author Cesar Himura
*/
class Font
{
    private:
        TTF_Font *font;
        int x;
		int y;
		int width;
		int height;
		int x_error;
		double alpha;
		bool center;
		GLuint img;

		/*** FUNCIONES ***/
		SDL_Surface* CreateTexture(SDL_Surface *temp);
		void draw();
		void drawString(char* text, SDL_Color color);
		int PowerOfTwo(int x);

    public:
        Font(char* nameFont, int size);
        ~Font();
        void drawString(char* text, int x, int y, SDL_Color color);
        void setX(double x){this->x = x;};
		void setY(double y){this->y = y;};
		void setWidth(int width){this->width = width;};
		void setHeight(int height){this->height = height;};
		void setFade(double alpha){this->alpha = alpha;};
        int getX(){return x;};
		int getY(){return y;};
		int getWidth(){return width;};
		int getHeight(){return height;};
		double getFade(){return alpha;};
        static const SDL_Color RED;
        static const SDL_Color GREEN;
        static const SDL_Color BLUE;
        static const SDL_Color WHITE;
        static const SDL_Color BLACK;
        static const SDL_Color CYAN;
        static const SDL_Color YELLOW;
        static const SDL_Color PINK;
        static const SDL_Color ORANGE;
        static const SDL_Color GRAY;
        static const SDL_Color MULBERRY;
        static const int CENTER = -10;
        static const int LEFT = -20;
        static const int RIGHT = -30;
};

#endif // FONT_H
