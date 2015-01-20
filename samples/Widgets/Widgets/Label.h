#pragma once

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include "Control.h"

#include <string>

class Label : public Control
{
public:
	Label();
	
	void SetFont(const std::string &filename);
	void SetText(const std::string &text);
	void Draw() override;
	
private:
	SDL::TTF::Font font;
	
	std::string text;
};