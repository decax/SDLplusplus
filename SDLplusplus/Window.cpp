#include "Window.h"

#include <exception>
#include <cassert>

namespace SDL {

std::map<uint32_t, Window *> Window::windows;
	
Window::Window(std::string p_name, const Size &p_size)
{
	Create(p_name, p_size);
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}

void Window::Create(std::string p_name, const Size &p_size)
{
	window = SDL_CreateWindow(p_name.c_str(), 0, 0, p_size.Width, p_size.Height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		throw std::exception();
	}
	
	windows.insert(std::pair<uint32_t, Window *>(GetID(), this));
}
	
void Window::SetPosition(const SDL::Point &p_position)
{
	assert(window != nullptr);
	
	SDL_SetWindowPosition(window, p_position.X, p_position.Y);
}

bool Window::IsFullscreen() const
{
	return (SDL_GetWindowFlags(window) & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP)) != 0;
}

void Window::SetFullscreen(bool p_fullscreen, bool p_useDesktopSize)
{
	SDL_SetWindowFullscreen(window, p_fullscreen ? (p_useDesktopSize ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_FULLSCREEN) : 0);
}

Size Window::GetSize() const
{
	Size size;
	
	SDL_GetWindowSize(window, &size.Width, &size.Height);
	
	return size;
}
	
uint32_t Window::GetID() const
{
	return SDL_GetWindowID(window);
}
	
Window& Window::GetWindowFromID(uint32_t ID)
{
	return *windows[ID];
}

}