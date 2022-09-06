#include "Sprite.h"

/**
* Constructor de la clase Sprite, este hace el calculo de las dimensiones del grafico (textura) y el centro
* de este lo coloca en la coordenada (0,0) del grafico, esto basado en OpenGL
* @param file Archivo de donde cargara la textura (imagen)
*/
Sprite::Sprite(const char *file)
{
	SDL_Surface *surface = IMG_Load(file);

  	height = surface->h;
	width = surface->w;

	nofcolors = surface->format->BytesPerPixel;

	//contains an alpha channel
	if(nofcolors==4)
	{
		if(surface->format->Rmask==0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	}
	else if(nofcolors==3) //no alpha channel
	{
		if(surface->format->Rmask==0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	}
	else
	{
		printf("warning: the image is not truecolor…this will break ");
	}

	glGenTextures(1, &img);
	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, img);

	// Set the texture’s stretching properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, nofcolors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);

	if(surface){
		SDL_FreeSurface(surface);
	}

	alpha = 1.0f;
	setAngle(90.0f);
}

Sprite::Sprite()
{
    //Agrego este constructor porque SpriteAnimated lo necesita
    //Revisar la herencia de C++ ¿No mete constructor por default?
}

/**
* Actualiza la logica del Sprite
*/
void Sprite::update()
{

}


/**
* Dibuja los graficos en pantalla
*/
void Sprite::render()
{
	glLoadIdentity();

	glTranslatef(x, y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);

	glEnable(GL_TEXTURE_2D);

	// Bind the texture to which subsequent calls refer to
	glBindTexture(GL_TEXTURE_2D, img);

	//Para que aparezca la imagen PNG con transparencia
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, alpha);

	if(alpha < 1.0f)
	{
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	glBegin(GL_QUADS);
		// Top-left vertex (corner)
		glTexCoord2i(0, 1);
		glVertex3f(-width/2, -height/2, 0);

		// Top-right vertex (corner)
		glTexCoord2i(1, 1);
		glVertex3f(width/2, -height/2, 0);

		// Bottom-right vertex (corner)
		glTexCoord2i(1, 0);
		glVertex3f(width/2, height/2, 0);

		// Bottom-left vertex (corner)
		glTexCoord2i(0, 0);
		glVertex3f(-width/2, height/2, 0);
	glEnd();
	glLoadIdentity();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_BLEND);
}

/**
* Destruye todo lo que ha cargado la clase Sprite y libera los recursos
*/
Sprite::~Sprite()
{
	glDeleteTextures(1, &img);
}


/**
* Asigna el angulo del sprite relacionado a OpenGL a partir de este calcula el angulo real
* @param angle Es el angulo que asignara para realizar la rotacion
*/
void Sprite::setAngle(double angle)
{
	this->angle = angle;

	if(angle + 90 > 360)
		angleReal = angle + 90 - 360;
	else
		angleReal = angle + 90;
}
