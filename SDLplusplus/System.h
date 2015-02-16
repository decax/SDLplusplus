#pragma once

#include "Event.h"
#include "Rect.h"
#include "PixelFormat.h"

#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include <functional>
#include <list>
#include <vector>
#include <string>
#include <map>

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
	
	void Update();
	
	enum EventAction
	{
		Add  = SDL_ADDEVENT,
		Peek = SDL_PEEKEVENT,
		Get  = SDL_GETEVENT
	};
	
	void PumpEvents();
	int PeepEvents(Event *events, int numEvents, EventAction eventAction, Event::Type minType, Event::Type maxType);
	void PollEvents();
	std::list<Event> Events;
	
	void RegisterEvent(Event::Type, std::function<void(const Event &)>);
	void UnregisterEvent(Event::Type, std::function<void(const Event &)>);
	
	uint32_t GetTicks() const;
	void Delay(uint32_t milliseconds) const;

	DisplayMode GetDesktopDisplayMode() const;
	
	std::string GetPixelFormatName(PixelFormat pixelFormat);
	
//	SDL_TimerID AddTimer(uint32_t interval, std::function<void(void)> callback) const;
//	void RemoveTimer(SDL_TimerID timerID) const;
	
private:
	std::map<Event::Type, std::list<std::function<void(const Event &)>>> registeredEvents;
};
	
inline System::SubSystem operator|(System::SubSystem a, System::SubSystem b) { return System::SubSystem(int(a) | int(b)); }

}