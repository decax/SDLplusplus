#include "System.h"

namespace SDL {

System::System(SubSystem p_subSystem)
{
	Init(p_subSystem);
}

System::~System()
{
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

void System::PollEvent()
{
	SDL_Event event;
	
	SDL_PollEvent(&event);
	
	Events.push_back(Event(event));
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


}