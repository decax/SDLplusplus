#pragma once

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/Image.h>

#include "Control.h"

class Picture : public Control
{
public:
	Picture() {}
	
	void SetImage(const SDL::Surface &image);
	
	void Draw() override;
	
	SDL::Point position;

private:
	SDL::Surface image;
	SDL::Texture texture;
	
	void CreateTextures() override;
};