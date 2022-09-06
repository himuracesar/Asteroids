#ifndef EXPLOSION_H
	#define EXPLOSION_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define TRUE  1
#define FALSE 0

#define MAX_PARTICLES 1000

#define SIZE 3
#define MAX_COLORS 20

class Explosion
{
    private:
        double x;
        double y;
        float slowdown; /* Slow Down Particles                                */
        float xspeed;          /* Base X Speed (To Allow Keyboard Direction Of Tail) */
        float yspeed;          /* Base Y Speed (To Allow Keyboard Direction Of Tail) */
        float zoom;   /* Used To Zoom Out                                   */
        GLuint loop;           /* Misc Loop Variable                                 */
        GLuint col;        /* Current Color Selection                            */
        //GLuint delay;          /* Rainbow Effect Delay                               */
        GLuint texture[1];     /* Storage For Our Particle Texture                   */

        GLfloat static colors[MAX_COLORS][3];

        /**Funciones*/
        int LoadGLTextures();
        void ResetParticle(int num, int color, float xDir, float yDir, float zDir);

        /* Create our particle structure */
        typedef struct
        {
            int   active; /* Active (Yes/No) */
            float life;   /* Particle Life   */
            float fade;   /* Fade Speed      */

            float r;      /* Red Value       */
            float g;      /* Green Value     */
            float b;      /* Blue Value      */

            float x;      /* X Position      */
            float y;      /* Y Position      */
            float z;      /* Z Position      */

            float xi;     /* X Direction     */
            float yi;     /* Y Direction     */
            float zi;     /* Z Direction     */

            float xg;     /* X Gravity       */
            float yg;     /* Y Gravity       */
            float zg;     /* Z Gravity       */
        } particle;

        particle particles[MAX_PARTICLES];

    public:
        Explosion(double x, double y);//, int size, int numParticles);
        ~Explosion();
        void update();
        void render();
        bool isDead();
};

#endif