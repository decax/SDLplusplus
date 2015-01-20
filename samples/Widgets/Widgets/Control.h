#pragma once

#include <SDLplusplus/SDLplusplus.h>

class Control
{
	friend class GUI;
	
public:
	Control();
	virtual ~Control() {}
	
	virtual void CreateTextures() {}
	
	virtual void Update() {}
	virtual void Draw() {}
	
	virtual void SetRenderer(SDL::Renderer &renderer);
	
protected:
	SDL::Renderer *renderer;
};