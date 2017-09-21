#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();
	void Resume();
	void Pause();
	Uint32 Read();
	Uint32 ReadSec();
	Uint32 Read_ms();

private:

	bool	running;
	Uint32	started_at;
	Uint32	stopped_at;
	Uint32	actual_ms;
	Uint32 paused_at;
	Uint32	last_ms;
};

#endif //__TIMER_H__