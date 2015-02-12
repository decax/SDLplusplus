#pragma once

#include "Control.h"
#include "Label.h"

#include <SDLplusplus/SDLplusplus.h>

#include <functional>


class Button : public Control
{
public:
	enum State
	{
		NORMAL, PRESSED, HOVERED, DEACTIVATED
	};
	
	Button();
	
	void SetRenderer(SDL::Renderer &renderer) override;
	
	void CreateTextures() override;
	
	void SetFont(const std::string &filename);
	void SetText(const std::string &string);
	
	void SetPosition(const SDL::Point &position) override;
	
	void DrawBackground() override;
	void DrawForeground() override;
	
	void Hover(bool hovered) override;
	void Press() override;
	void Release(bool clicked) override;
	
	void Click();
	void OnClick(std::function<void()> onClick);
	
private:
	State state;
	
	Label label;
	
	SDL::Texture textures[4];
	
	std::function<void()> clickedCallback;
	
	void UpdateLabelPosition();
};