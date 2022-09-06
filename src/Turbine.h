#ifndef TURBINE_H
	#define TURBINE_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define TRUE  1
#define FALSE 0

#define MAX_PARTICLES 1000

#define SIZE 8
#define MAX_COLORS 12

class Turbine
{
    private:
        double x;
        double y;
        double gravityX;
        double gravityY;
        double angle;
        float slowdown; /* Slow Down Particles                                */
        float xspeed;          /* Base X Speed (To Allow Keyboard Direction Of Tail) */
        float yspeed;          /* Base Y Speed (To Allow Keyboard Direction Of Tail) */
        float zoom;   /* Used To Zoom Out                                   */
        bool resetParticles;
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
        Turbine(double x, double y);
        ~Turbine();
        void update();
        void render();
        void setX(double x){this->x = x;};
        void setY(double y){this->y = y;};
        void setGravityX(double gravityX){this->gravityX = gravityX;};
        void setGravityY(double gravityY){this->gravityY = gravityY;};
        void setAngle(double angle){this->angle = angle;};
        void setFlame(float flame){slowdown = flame;};
        void setResetParticles(bool reset){resetParticles = reset;};
        double getX(){return x;};
        double getY(){return y;};
        double getGravityX(){return gravityX;};
        double getGravityY(){return gravityY;};
        double getAngle(){return angle;};
        float getFlame(){return slowdown;};
        bool isResetParticles(){return resetParticles;};
};

#endif
