#include "KidIcarus.h"

#include <SDLplusplus/Image.h>

#include <iostream>

using namespace std;
using namespace SDL;

KidIcarus::KidIcarus()
: system(System::SubSystem::EVERYTHING),
  window("Kid Icarus", Size(800, 600)),
  renderer(window, Renderer::TypeFlag::ACCELERATED | Renderer::TypeFlag::PRESENT_VSYNC),
  pit(renderer),
  snake(renderer)
{
	srand(System::GetTicks());
	
	system.RegisterEvent(Event::QUIT,     [&](const Event &) { running = false; });
	system.RegisterEvent(Event::KEY_DOWN, bind(&KidIcarus::OnKeyDown, this, placeholders::_1));
	system.RegisterEvent(Event::KEY_UP,   bind(&KidIcarus::OnKeyUp,   this, placeholders::_1));
	
	StartGame();
}

void KidIcarus::StartGame()
{
	running = true;
}

void KidIcarus::OnKeyDown(const Event &event)
{
	auto kbe = (const KeyboardEvent &)event;
	
	switch (kbe.GetScancode()) {
			
		case Scancode::ESCAPE:
			running = false;
			break;
			
		case Scancode::RETURN:
			cout << "Shoot" << endl;
			break;
			
		case Scancode::LEFT:
			pit.SetDirection(Direction::LEFT);
			break;
			
		case Scancode::RIGHT:
			pit.SetDirection(Direction::RIGHT);
			break;
			
		case Scancode::DOWN:
			pit.Crouch();
			break;
			
		case Scancode::UP:
			pit.LookUp();
			break;

		default:
			// don't care
			break;
	}
}

void KidIcarus::OnKeyUp(const Event &event)
{
	auto kbe = (const KeyboardEvent &)event;
	
	switch (kbe.GetScancode()) {
			
		case Scancode::LEFT:
			pit.SetDirection(Direction::LEFT, false);
			break;
			
		case Scancode::RIGHT:
			pit.SetDirection(Direction::RIGHT, false);
			break;
			
		case Scancode::DOWN:
			pit.Crouch(false);
			break;
			
		case Scancode::UP:
			pit.LookUp(false);
			break;
			
		default:
			// don't care
			break;
	}
}

void KidIcarus::Run()
{
	while (running) {
		system.Update();
		
		// Update
		{
			time.Update();
			
			pit.Update(time);
			snake.Update(time);
		}
		
		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		pit.Draw();
		snake.Draw();
		
		renderer.Present();
	}
}