#include "Joystick.h"

namespace SDL {

#include <cassert>

Joystick::Joystick()
{
	joystick = nullptr;
}
	
Joystick::~Joystick()
{
	SDL_JoystickClose(joystick);
}

bool Joystick::IsGameController(int deviceIndex) const
{
	assert(deviceIndex < SDL_NumJoysticks());
	
	return SDL_IsGameController(deviceIndex);
}


void Joystick::Open(int p_deviceIndex)
{
	assert(p_deviceIndex < SDL_NumJoysticks());

	joystick = SDL_JoystickOpen(p_deviceIndex);
}

std::vector<std::string> Joystick::GetJoystickNames() const
{
	int numJoysticks = SDL_NumJoysticks();
	
	std::vector<std::string> joystickNames;
	joystickNames.reserve(numJoysticks);
	
	for (int i = 0; i < numJoysticks; i++) {
		joystickNames.push_back(SDL_JoystickNameForIndex(i));
	}
	
	return joystickNames;
}
	
int Joystick::GetNumAxes() const
{
	return SDL_JoystickNumAxes(joystick);
}

int Joystick::GetNumBalls() const
{
	return SDL_JoystickNumBalls(joystick);
}

int Joystick::GetNumHats() const
{
	return SDL_JoystickNumHats(joystick);
}

int Joystick::GetNumButtons() const
{
	return SDL_JoystickNumButtons(joystick);
}
	
uint8_t Joystick::GetButton(int p_button)
{
	return SDL_JoystickGetButton(joystick, p_button);
}


}