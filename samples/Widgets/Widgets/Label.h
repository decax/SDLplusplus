#pragma once

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include "Control.h"

#include <string>

class Label : public Control
{
	friend class Button;
	
public:
	void CreateTextures() override;
	
	void SetFont(const std::string &filename);
	void SetText(const std::string &text);
	
protected:
	void DrawForeground() override;

private:
	SDL::TTF::Font font;
	
	std::string text;
	
	SDL::Size textSize;
	void UpdateTextSize();
};