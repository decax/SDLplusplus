#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <map>

#include "Rect.h"

namespace SDL {

class Renderer;

class Window
{
	friend class Renderer;
	
public:
	Window() {}
	Window(std::string name, const Size &size);
	~Window();
	
	void Create(std::string name, const Size &size);
	void SetPosition(const Point &position);
	
	bool IsFullscreen() const;
	void SetFullscreen(bool fullscreen, bool useDesktopSize);
	
	uint32_t GetID() const;
	
	Size GetSize() const;
	
	static Window& GetWindowFromID(uint32_t ID);
	
private:
	SDL_Window *window;

	static std::map<uint32_t, Window *> windows;
};

}