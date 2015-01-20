#pragma once

#include "Control.h"
#include "Label.h"

#include <SDLplusplus/SDLplusplus.h>

#include <functional>

class Button : public Control
{
public:
	Button();
	
	void SetRenderer(SDL::Renderer &renderer) override;
	
	void CreateTextures();
	
	void SetFont(const std::string &filename);
	void SetText(const std::string &string);
	
	void SetPosition(const SDL::Point &position);
	
	void Draw() override;
	
	void Release(bool trigger) override;
	
	void OnClick(std::function<void()> onClick);
	
private:
	Label label;
	
	SDL::Texture textures[2];
	
	std::function<void()> onClick;
};