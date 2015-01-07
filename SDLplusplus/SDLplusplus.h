#pragma once

#include "System.h"
#include "Window.h"
#include "Renderer.h"
#include "Surface.h"
#include "Texture.h"
#include "Audio.h"
#include "Joystick.h"
#include "GameController.h"
#include "Point.h"
#include "Size.h"
#include "Rect.h"
#include "Color.h"
#include "Scancode.h"
#include "BlendMode.h"

// TODO:
// - check for move constructor correctness
// - check for copy constructor correctness
// - implement missing stuff
// - add error handling
// - add documentation
// - add samples
// - package in a unix/windows friendly way

// include the original SDL2 for convenience
#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif