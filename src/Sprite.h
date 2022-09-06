#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

using std::string;

/**
* Clase que gestiona los graficos de los objetos que son
* renderizados en pantalla
*/
class Sprite
{
	private:
		double x;
		double y;
		double angle;
		double angleReal;
		double angleDir;
		double vx;
		double vy;
		double alpha;
		int width;
		int height;
		GLuint img;
		GLint nofcolors;
		GLenum texture_format;
		string name;


	public:
		Sprite(const char *file);
		Sprite();
		~Sprite();
		void setX(double x){this->x = x;};
		void setY(double y){this->y = y;};
		void setVx(double vx){this->vx = vx;};
		void setVy(double vy){this->vy = vy;};
		void setAngle(double angle);
		void setAngleDirection(double angle){angleDir = angle;};
		void virtual update();
		void virtual render();
		void setName(string name){this->name = name;};
		void setWidth(int width){this->width = width;};
		void setHeight(int height){this->height = height;};
		void setFade(double alpha){this->alpha = alpha;};
		double getX(){return x;};
		double getY(){return y;};
		double getAngle(){return angle;};
		double getAngleReal(){return angleReal;};
		double getAngleDirection(){return angleDir;};
		double getVx(){return vx;};
		double getVy(){return vy;};
		double getFade(){return alpha;};
		int getWidth(){return width;};
		int getHeight(){return height;};
   		string getName(){return name;};
};

#endif
