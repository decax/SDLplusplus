#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <vector>

namespace SDL {
	
class Joystick
{
public:
	Joystick();
	~Joystick();
	
	bool IsGameController(int deviceIndex) const;
	
	void Open(int deviceIndex);
	
	std::vector<std::string> GetJoystickNames() const;
	
	int GetNumAxes() const;
	int GetNumBalls() const;
	int GetNumHats() const;
	int GetNumButtons() const;
	
	uint8_t GetButton(int button);
	
private:
	SDL_Joystick *joystick;
};

}