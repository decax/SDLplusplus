#include "Control.h"

#include <SDLplusplus/SDLplusplus.h>

Control::Control()
{
	renderer = nullptr;
}

void Control::SetRenderer(SDL::Renderer &p_renderer)
{
	renderer = &p_renderer;
}