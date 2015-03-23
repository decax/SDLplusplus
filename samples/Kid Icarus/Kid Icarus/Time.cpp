#include "Time.h"

#include <SDLplusplus/SDLplusplus.h>

void TimeSpan::Update()
{
	millisec = SDL::System::GetTicks();
}

void Time::Update()
{
	previous = now;

	now.Update();
}