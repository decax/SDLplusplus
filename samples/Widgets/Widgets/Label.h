#pragma once

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include "Control.h"

#include <string>

class Label : public Control
{
	friend class Button;
	
public:
	enum Alignment {
		LEFT, CENTER, RIGHT
	};
	
	Label();
	
	void CreateTextures() override;
	
	void SetFont(const std::string &filename);
	void SetText(const std::string &text);
	
	void SetAlignment(Alignment alignment);
	
protected:
	void DrawForeground() override;

private:
	SDL::TTF::Font font;
	
	std::string text;
	
	Alignment alignment;
	
	SDL::Size textSize;
	void UpdateTextSize();
};

inline void Label::SetAlignment(Alignment p_alignment)
{
	alignment = p_alignment;
}
