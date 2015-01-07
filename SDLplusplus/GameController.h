#pragma once

#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

namespace SDL {
	
class GameController
{
public:
	enum Button
	{
		A              = SDL_CONTROLLER_BUTTON_A,
		B              = SDL_CONTROLLER_BUTTON_B,
		X              = SDL_CONTROLLER_BUTTON_X,
		Y              = SDL_CONTROLLER_BUTTON_Y,
		BACK           = SDL_CONTROLLER_BUTTON_BACK,
		GUIDE          = SDL_CONTROLLER_BUTTON_GUIDE,
		START          = SDL_CONTROLLER_BUTTON_START,
		LEFT_STICK     = SDL_CONTROLLER_BUTTON_LEFTSTICK,
		RIGHT_STICK    = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
		LEFT_SHOULDER  = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
		RIGHT_SHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
		DPAD_UP        = SDL_CONTROLLER_BUTTON_DPAD_UP,
		DPAD_DOWN      = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		DPAD_LEFT      = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		DPAD_RIGHT     = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	};
	
	~GameController();
	
	void Open(int joystickIndex);
	void Close();
	
	bool GetButton(Button button) const;
	
private:
	SDL_GameController *gameController;
};

}