#pragma once

#include <SDLplusplus/SDLplusplus.h>

#include "Label.h"

class Button
{
public:
	Button(SDL::Renderer &renderer);
	
	void SetFont(const std::string &filename);
	void SetText(const std::string &string);
	
	void SetPosition(const SDL::Point &position);
	
	void Draw();
	
private:
	SDL::Renderer &renderer;
	SDL::Size size;
	SDL::Point position;
	
	Label label;
	
	SDL::Texture textures[2];
};