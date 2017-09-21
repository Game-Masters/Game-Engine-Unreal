// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"

// ---------------------------------------------
Timer::Timer()
{
	Start();
}

// ---------------------------------------------
void Timer::Start()
{
	running = true;
	this->started_at = SDL_GetTicks();
	this->paused_at = 0;
}

// ---------------------------------------------
void Timer::Stop()
{
	running = false;
	stopped_at = SDL_GetTicks();
	actual_ms += (SDL_GetTicks() - started_at);
	
	last_ms = actual_ms;
	actual_ms = 0;
	
}

void Timer::Resume()
{
	started_at = SDL_GetTicks();
	}

void Timer::Pause()
 {
	actual_ms += (SDL_GetTicks() - started_at);
	
		
}

// ---------------------------------------------
Uint32 Timer::Read()
{
	if(running == true)
	{
		return SDL_GetTicks() - this->started_at;
	}
	else
	{
		return stopped_at - started_at;
	}
}

Uint32 Timer::ReadSec()
{
	if (running == true)
	{
		return (SDL_GetTicks() - started_at)/1000;
	}
	else
	{
		return (stopped_at - started_at)/1000;
	}
}
Uint32 Timer::Read_ms(){

	if (this->last_ms > 2)
	int x = 0;
	return this->last_ms;
}


