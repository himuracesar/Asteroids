#ifndef TIMER_H
    #define TIMER_H

#include "SDL.h"

/**
* Clase Timer. La tome de la pagina de Lazy Foo pero le hice algunas modificaciones
* para que se adaptara a lo que necesito
* @author Lazy Foo' Productions
*         Cesar Himura (mod)
*/
class Timer
{
    private:
        //The clock time when the timer started
        int startTicks;

        //The ticks stored when the timer was paused
        int pausedTicks;
        int time;

        //The timer status
        bool paused;
        bool started;

    public:
        //Initializes variables
        Timer(int miliSeconds);

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        int get_ticks();

        //Checks the status of the timer
        bool is_started();
        bool is_paused();
        bool is_time();

        void setTime(int miliSeconds){time = miliSeconds;};
};

#endif // TIMER_H
