#pragma once

#include "Control.h"

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <list>

class GUI
{
public:
	GUI(SDL::System &system, SDL::Renderer &renderer);
	~GUI();
	
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
	
	SDL::Point mousePosition;
	
	void OnMouseMotion(const SDL::Event &event);
	void OnMouseDown(const SDL::Event &event);
	void OnMouseUp(const SDL::Event &event);
	void OnMouseWheel(const SDL::Event &event);
};
