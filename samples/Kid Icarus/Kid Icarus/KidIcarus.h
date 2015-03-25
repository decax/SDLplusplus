#pragma once

#include <SDLplusplus/SDLplusplus.h>

#include "Pit.h"
#include "Snake.h"

#include "Time.h"
#include "Type.h"

class KidIcarus
{
public:
	KidIcarus();
	
	void Run();
	
private:
	void StartGame();
	void OnKeyDown(const SDL::Event &event);
	void OnKeyUp(const SDL::Event &event);
	
	SDL::System system;
	SDL::Window window;
	SDL::Renderer renderer;
	
	Time time;
	
	Pit pit;
	Snake snake;
	
	bool running;
};