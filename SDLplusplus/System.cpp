#include "System.h"

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
	
void System::RegisterEvent(Event::Type eventType, function<void(const Event &)> callback)
{
	registeredEvents[eventType] = callback;
}

void System::Update()
{
	PollEvents();
}
	
void System::PollEvents()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		Event e(event);
		Events.push_back(e);
		
		auto it = registeredEvents.find(e.GetType());
		if (it != registeredEvents.end()) {
			(it->second)(e);
		}
	}
}

void System::Delay(uint32_t p_milliseconds) const
{
	SDL_Delay(p_milliseconds);
}
	
uint32_t System::GetTicks() const
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