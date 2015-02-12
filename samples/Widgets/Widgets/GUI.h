#pragma once

#include "Control.h"

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <list>

class GUI
{
public:
	GUI(SDL::System &system, SDL::Renderer &renderer);
	
	void AddControl(Control &control);
	
	void Update();
	void Draw();
	
private:
	SDL::System &system;
	SDL::Renderer &renderer;
	
	SDL::TTF ttf;
	
	std::list<Control *> controls;
	Control *hoveredControl;
	Control *pressedControl;
};
