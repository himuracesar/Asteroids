#include "Font.h"

const SDL_Color Font::RED = {255, 0, 0};
const SDL_Color Font::GREEN = {0, 255, 0};
const SDL_Color Font::BLUE = {0, 0, 255};
const SDL_Color Font::WHITE = {255, 255, 255};
const SDL_Color Font::BLACK = {0, 0, 0};
const SDL_Color Font::CYAN = {0, 255, 255};
const SDL_Color Font::YELLOW = {255, 255, 0};
const SDL_Color Font::PINK = {255, 0, 255};
const SDL_Color Font::ORANGE = {255, 150, 0};
const SDL_Color Font::GRAY = {209, 209, 213};
const SDL_Color Font::MULBERRY = {126, 7, 248};

/**
* Contructor de la clase Font
* @param nameFont Nombre de la fuente
* @param size Tamanio con la que escribira
* @author Cesar Himura
*/
Font::Font(char* nameFont, int size)
{
    font = TTF_OpenFont(nameFont,size);

    alpha = 1.0f;
	center = false;
	x_error = 0;

	img = NULL;
}

/**
* Destructor de la clase Font
*/
Font::~Font()
{
    TTF_CloseFont(font);
    glDeleteTextures(1, &img);
}

/**
* Crea la textura con el texto a partir de una imagen previamente generada
* @param temp Es la imagen con el texto previamente generada
*/
SDL_Surface* Font::CreateTexture(SDL_Surface *temp)
{
	int w,h;

	SDL_Surface *image;

    Uint32 saved_flags;
    Uint8  saved_alpha;

	/* Convert the rendered text to a known format */
	w = PowerOfTwo(temp->w);
	h = PowerOfTwo(temp->h);

	if(center)
		x_error = (w - temp->w)/2;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
      image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, temp->format->BitsPerPixel,
                                  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    #else
      image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, temp->format->BitsPerPixel,
                                  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    #endif


    /* Save the alpha blending attributes */
	saved_flags = temp->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	saved_alpha = temp->format->alpha;
	if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
	{
		SDL_SetAlpha(temp, 0, 0);
	}

	/*int colorkey = SDL_MapRGB(temp->format, 255, 0, 255);
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
	SDL_FillRect(image, 0, colorkey);*/

    SDL_BlitSurface(temp, 0, image, 0);

    this->setWidth(w);
    this->setHeight(h);

    SDL_FreeSurface(temp);

    return(image);
}

/**
* Escribe una cadena en pantalla
* @param text Texto a pintar en pantalla
* @param x Coordenada en X - Aqui se le puede enviar algun dato de alineacion
* para que el texto quede alineado en la pantalla
* @param y Coordenada en Y
* @param color Color con el que pintara la cadena
*/
void Font::drawString(char* text, int x, int y, SDL_Color color)
{
    drawString(text, color);

    switch(x)
    {
        case CENTER:
			center = true;
            this->setX(WIDTH_SCREEN/2-this->getWidth()/2);
        break;
        case LEFT:
			x_error = 0;
            this->setX(0);
        break;
        case RIGHT:
			x_error = 0;
            this->setX(WIDTH_SCREEN-this->getWidth());
        break;
        default:
			x_error = 0;
            this->setX(x);
        break;
    }

    this->setY(y);

    draw();
}

/**
* Dibuja en la pantalla
*/
void Font::draw()
{
	glLoadIdentity();
	
	glEnable(GL_TEXTURE_2D);

    glTranslatef(this->getX() + x_error, this->getY(), 0.0);

	glBindTexture(GL_TEXTURE_2D, img);

	glColor4f(1.0f, 1.0f, 1.0f, alpha);

	if(alpha < 1.0f)
	{
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	glBegin(GL_QUADS);
		glTexCoord2i(1, 1);
		glVertex3f(this->getWidth(), this->getHeight(), 0);

		glTexCoord2i(0, 1);
		glVertex3f(0, this->getHeight(), 0);

		glTexCoord2i(0, 0);
		glVertex3f(0, 0, 0);

		glTexCoord2i(1, 0);
		glVertex3f(this->getWidth(), 0, 0);
	glEnd();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_2D);
	glLoadIdentity();
}

/**
* Escribe una cadena en pantalla
* @param text Texto a pintar en pantalla
* @param color Color con el que pintara la cadena
*/
void Font::drawString(char* text, SDL_Color color)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_Surface *surf_text = NULL;

	if(text != NULL && font != NULL)
		surf_text = TTF_RenderText_Blended(font, text, color);

	if(surf_text != NULL)
	{
		SDL_Surface *surf = CreateTexture(surf_text);

		glDeleteTextures(1, &img);
		glGenTextures(1, &img);
		glBindTexture(GL_TEXTURE_2D, img);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, surf->w, surf->h,0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
		//printf("W:: %d, H:: %d\n", surf->w, surf->h);
		//glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, 312, 102,0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

		SDL_FreeSurface(surf);
	}
}

int Font::PowerOfTwo(int x)
{
	double logbase2 = log((double)x) / log((double)2);

	//return round(pow(2,ceil(logbase2)));
	return ceil(pow(2,ceil(logbase2)));
}