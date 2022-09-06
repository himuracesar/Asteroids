#include "Turbine.h"

GLfloat Turbine::colors[MAX_COLORS][3] =
{
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f},
    {0.15f,  0.84f,  0.87f}
};

Turbine::Turbine(double x, double y)
{
    this->x = x;
    this->y = y;

    resetParticles = true;

    texture[0] = 0;

    slowdown = 0.5f; /* Slow Down Particles */
    zoom = -400.0f;
    col = 0;

    LoadGLTextures();

    for(loop = 0; loop < MAX_PARTICLES; loop++)
    {
       int color = (loop + 1) / (MAX_PARTICLES / MAX_COLORS);
       float xi, yi, zi;
       xi = 0.0f;//(float)((rand() % 50) - 26.0f) * 10.0f;
       yi = zi = 0.0f;//(float)((rand() % 50) - 25.0f) * 10.0f;

       ResetParticle(loop, color, xi, yi, zi);
    }
}

Turbine::~Turbine()
{
    glDeleteTextures(1, &texture[0]);
}


/*int Turbine::LoadGLTextures()
{
    // Status indicator
    int Status = FALSE;

    // Create storage space for the texture
    SDL_Surface *TextureImage[1];

    // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
    if((TextureImage[0] = SDL_LoadBMP("images/particle.bmp")))
	//if((TextureImage[0] = IMG_Load("images/particle.png")))
    {
	    // Set the status to true
	    Status = TRUE;

	    // Create The Texture
	    glGenTextures(1, &texture[0]);

	    // Typical Texture Generation Using Data From The Bitmap
	    glBindTexture(GL_TEXTURE_2D, texture[0]);

	    // Generate The Texture
	    glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->w, TextureImage[0]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage[0]->pixels);

	    // Linear Filtering
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Free up any memory we may have used
    if ( TextureImage[0] )
	    SDL_FreeSurface( TextureImage[0] );

    return Status;
}
*/
int Turbine::LoadGLTextures()
{
	SDL_Surface *bg; // this surface will tell us the details of the image

	GLuint nofcolors = NULL;
    GLuint texture_format = NULL;

	if((bg = IMG_Load("images/particle.png")))
	{
		// Check that the image’s width is a power of 2
		if ((bg->w & (bg->w - 1)) != 0){
			printf("warning: image.bmp’s width is not a power of 2\n");
		}

		// Also check if the height is a power of 2
		if ( (bg->h & (bg->h - 1)) != 0 ) {
			printf("warning: image.bmp’s height is not a power of 2\n");
		}

		//get number of channels in the SDL surface
		nofcolors=bg->format->BytesPerPixel;

		//contains an alpha channel
		if(nofcolors==4)
		{
			if(bg->format->Rmask==0x000000ff)
				texture_format=GL_RGBA;
			else
				texture_format=GL_BGRA;
		}
		else if(nofcolors==3) //no alpha channel
		{
			if(bg->format->Rmask==0x000000ff)
				texture_format=GL_RGB;
			else
				texture_format=GL_BGR;
		}
		else
		{
			printf("warning: the image is not truecolor…this will break ");
		}

		// Have OpenGL generate a texture object handle for us
		if(texture[0] != NULL)
            glDeleteTextures(1, &texture[0]);
        glGenTextures(1, &texture[0]);
		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		// Set the texture’s stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexImage2D(GL_TEXTURE_2D, 0, nofcolors, bg->w, bg->h, 0, texture_format, GL_UNSIGNED_BYTE, bg->pixels);
	}
	else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Free the SDL_Surface only if it was successfully created
	if (bg) {
		SDL_FreeSurface(bg);
	}

	return 0;
}

void Turbine::ResetParticle(int num, int color, float xDir, float yDir, float zDir)
{
    /* Make the particels active */
    particles[num].active = TRUE;
    /* Give the particles life */
    particles[num].life = 1.0f;
    /* Random Fade Speed */
    particles[num].fade = (float)(rand() %100) / 1000.0f + 0.003f;
    /* Select Red Rainbow Color */
    particles[num].r = colors[color][0];
    /* Select Green Rainbow Color */
    particles[num].g = colors[color][1];
    /* Select Blue Rainbow Color */
    particles[num].b = colors[color][2];
    /* Set the position on the X axis */
    particles[num].x = x;
    /* Set the position on the Y axis */
    particles[num].y = y;
    /* Set the position on the Z axis */
    particles[num].z = 0.0f;
    /* Random Speed On X Axis */
    particles[num].xi = xDir;
    /* Random Speed On Y Axi */
    particles[num].yi = yDir;
    /* Random Speed On Z Axis */
    particles[num].zi = zDir;
    /* Set Horizontal Pull To Zero */
    particles[num].xg = gravityX;//1.0f;
    /* Set Vertical Pull Downward */
    //particles[num].yg = -5.0f;
    particles[num].yg = gravityY;//-2.0f;
    /* Set Pull On Z Axis To Zero */
    particles[num].zg = 0.0f;
}

void Turbine::update()
{
    glLoadIdentity();

    /* Modify each of the particles */
    for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
	    if (particles[loop].active)
		{
		    /* Grab Our Particle X Position */
		    float x = particles[loop].x;
		    /* Grab Our Particle Y Position */
		    float y = particles[loop].y;
		    /* Particle Z Position + Zoom */
		    float z = 0;//particles[loop].z + zoom;

		    /* Move On The X Axis By X Speed */
		    particles[loop].x += particles[loop].xi/(slowdown * 1000);
		    /* Move On The Y Axis By Y Speed */
		    particles[loop].y += particles[loop].yi/(slowdown * 1000);
		    /* Move On The Z Axis By Z Speed */
		    particles[loop].z += 0;//particles[loop].zi /(slowdown * 1000);

		    /* Take Pull On X Axis Into Account */
		    particles[loop].xi += particles[loop].xg;
		    /* Take Pull On Y Axis Into Account */
		    particles[loop].yi += particles[loop].yg;
		    /* Take Pull On Z Axis Into Account */
		    particles[loop].zi += particles[loop].zg;

		    /* Reduce Particles Life By 'Fade' */
		    particles[loop].life -= particles[loop].fade;

		    /* If the particle dies, revive it */
		    if(resetParticles)
		    {
                if(particles[loop].life < 0.0f)
                {
                    float xi, yi, zi;
                    xi = xspeed + (float)((rand() % 60) - 32.0f);
                    yi = yspeed + (float)((rand() % 60) - 30.0f);
                    zi = (float)((rand() % 60) - 30.0f);
                    ResetParticle(loop, col, xi, yi, zi);
                }
		    }
		}
	}//for
}

void Turbine::render()
{
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
	    if (particles[loop].active)
		{
		    glColor4f(particles[loop].r,
			          particles[loop].g,
                      particles[loop].b,
			          particles[loop].life);

		    /* Build Quad From A Triangle Strip */
		    glBegin(GL_TRIANGLE_STRIP);
		      /* Top Right */
		      glTexCoord2d( 1, 1 );
		      glVertex3f( particles[loop].x + SIZE, particles[loop].y + SIZE, 0 );
		      /* Top Left */
		      glTexCoord2d( 0, 1 );
		      glVertex3f( particles[loop].x - SIZE, particles[loop].y + SIZE, 0 );
		      /* Bottom Right */
		      glTexCoord2d( 1, 0 );
		      glVertex3f( particles[loop].x + SIZE, particles[loop].y - SIZE, 0 );
		      /* Bottom Left */
		      glTexCoord2d( 0, 0 );
		      glVertex3f( particles[loop].x - SIZE, particles[loop].y - SIZE, 0 );
		    glEnd();
		}
	}

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_2D);
	glLoadIdentity();
}
