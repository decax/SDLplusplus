#pragma once

#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/Image.h>

#include "Control.h"

class Picture : public Control
{
public:
	Picture();
	
	void SetImage(const SDL::Surface &image);
	
protected:
	void DrawForeground() override;
	
private:
	SDL::Surface image;
	SDL::Texture texture;
	
	void CreateTextures() override;
};