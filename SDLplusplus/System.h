#pragma once

#include <SDL2/SDL.h>

#include <functional>
#include <list>

#include "Event.h"
#include "Rect.h"
#include "PixelFormat.h"

namespace SDL {

class DisplayMode
{
	friend class System;
	
public:
	PixelFormat GetPixelFormat() const;
	Size GetSize() const;
	int GetRefreshRate() const;
	
private:
	SDL_DisplayMode displayMode;
};
	
inline PixelFormat DisplayMode::GetPixelFormat() const
{
	return (PixelFormat)displayMode.format;
}

inline Size DisplayMode::GetSize() const
{
	return Size(displayMode.w, displayMode.h);
}

inline int DisplayMode::GetRefreshRate() const
{
	return displayMode.refresh_rate;
}
	
class System
{
public:
	enum SubSystem
	{
		TIMER           = SDL_INIT_TIMER,
		AUDIO           = SDL_INIT_AUDIO,
		VIDEO           = SDL_INIT_VIDEO,
		JOYSTICK        = SDL_INIT_JOYSTICK,
		HAPTIC          = SDL_INIT_HAPTIC,
		GAME_CONTROLLER = SDL_INIT_GAMECONTROLLER,
		EVENTS          = SDL_INIT_EVENTS,
		NO_PARACHUTE    = SDL_INIT_NOPARACHUTE,
		EVERYTHING      = SDL_INIT_EVERYTHING
	};
	
	System(SubSystem subSystem);
	~System();
	
	void Init(SubSystem subSystem);
	void InitSubSystem(SubSystem subSystem);
	void QuitSubSystem(SubSystem subSystem);
	
	void PollEvent();
	std::list<Event> Events;
	
	uint32_t GetTicks() const;
	void Delay(uint32_t milliseconds) const;

	DisplayMode GetDesktopDisplayMode() const;
	
//	SDL_TimerID AddTimer(uint32_t interval, std::function<void(void)> callback) const;
//	void RemoveTimer(SDL_TimerID timerID) const;
};
	
inline System::SubSystem operator|(System::SubSystem a, System::SubSystem b) { return System::SubSystem(int(a) | int(b)); }

}