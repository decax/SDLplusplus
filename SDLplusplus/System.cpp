#include "System.h"

#include <cassert>

namespace SDL {

using namespace std;
	
System::System(SubSystem p_subSystem)
{
	Init(p_subSystem);
}

System::~System()
{
	registeredEvents.clear();

	SDL_Quit();
}

void System::Init(SubSystem p_subSystem)
{
	if (SDL_Init((int)p_subSystem) != 0) {
	}
}

void System::InitSubSystem(SubSystem p_subSystem)
{
	SDL_InitSubSystem((int)p_subSystem);
}

void System::QuitSubSystem(SubSystem p_subSystem)
{
	SDL_QuitSubSystem((int)p_subSystem);
}
	
void System::RegisterEvent(Event::Type p_eventType, function<void(const Event &)> p_callback)
{
	registeredEvents[p_eventType].push_back(p_callback);
}

void System::UnregisterEvent(Event::Type p_eventType, function<void(const Event &)> p_callback)
{
//	assert(registeredEvents[p_eventType] == p_callback);
//	registeredEvents[p_eventType] = nullptr;
}
	
void System::Update()
{
	PollEvents();
}
	
void System::PumpEvents()
{
	SDL_PumpEvents();
}

int System::PeepEvents(Event *p_events, int p_numEvents, EventAction p_eventAction, Event::Type p_minType, Event::Type p_maxType)
{
	return SDL_PeepEvents((SDL_Event *)p_events, p_numEvents, (SDL_eventaction)p_eventAction, p_minType, p_maxType);
}
	
void System::PollEvents()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		Event e(event);
		Events.push_back(e);
		
		auto it = registeredEvents.find(e.GetType());
		if (it != registeredEvents.end()) {
			for (auto f : it->second) {
				f(e);
			}
		}
	}
}

void System::Delay(uint32_t p_milliseconds) const
{
	SDL_Delay(p_milliseconds);
}
	
uint32_t System::GetTicks()
{
	return SDL_GetTicks();
}
	
DisplayMode System::GetDesktopDisplayMode() const
{
	DisplayMode displayMode;
	
	SDL_GetDesktopDisplayMode(0, &displayMode.displayMode);
	
	return displayMode;
}

//static void internal_timer_callback(void *p_userData)
//{
//	(std::function<void(void)>(p_userData))();
//}
//
//SDL_TimerID System::AddTimer(uint32_t p_interval, std::function<void(void)> p_callback) const
//{
//	extern DECLSPEC SDL_TimerID SDLCALL SDL_AddTimer(Uint32 interval,
//													 SDL_TimerCallback callback,
//													 void *param);
//	return SDL_AddTimer(p_interval, internal_timer_callback, p_callback);
//}

std::string System::GetPixelFormatName(PixelFormat p_pixelFormat)
{
	return SDL_GetPixelFormatName(p_pixelFormat);
}

}