#pragma once

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <string>

class Label
{
public:
	Label();
	
	void SetPosition(const SDL::Point &position);
	
	void SetFont(const std::string &filename);
	void SetText(const std::string &text);
	void Draw(SDL::Renderer &renderer);
	
private:
	SDL::TTF::Font font;
	
	std::string text;
	
	SDL::Point position;
};