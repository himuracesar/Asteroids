#include "Timer.h"

/**
* Constructor de la clase Time
* @param miliSecond Es el tiempo en segundos para el timer
*/
Timer::Timer(int miliSeconds)
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    time = miliSeconds;
    paused = false;
    started = false;
}

/**
* Inicializa el timer, empieza a correr el tiempo
*/
void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

/**
* Detiene el timer
*/
void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

/**
* Pausa el timer
*/
void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

/**
* Quita la pausa del timer
*/
void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

/**
* Obtiene los milisegundos que han pasado
*/
int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

/**
* Obtiene si el timer esta corriendo
* @return true Si ya fue inicializado
*/
bool Timer::is_started()
{
    return started;
}

/**
* Verifica si el timer esta pausado
* @return true Si el timer esta pausado
*/
bool Timer::is_paused()
{
    return paused;
}

/**
* Verifica si ha pasado el tiempo con el que fue construido
* @return true Si el tiempo estimado ha transcurrido
*/
bool Timer::is_time()
{
    if(time <= get_ticks())
        return true;

    return false;
}
