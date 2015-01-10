#include "Snake.h"

#include "Square.h"

#include <iostream>
#include <exception>

using namespace std;
using namespace SDL;

Snake::Snake()
: system(System::SubSystem::EVERYTHING),
  window("Snake", Size(800, 600)),
  renderer(window, Renderer::TypeFlag::ACCELERATED | Renderer::TypeFlag::PRESENT_VSYNC)
{
	srand((unsigned int)time(nullptr));
	
	gridSizeInSquares = Size(GRID_WIDTH_IN_SQUARES, GRID_HEIGHT_IN_SQUARES);
	
	gridSize = Size(gridSizeInSquares.Width * Square::Width, gridSizeInSquares.Height * Square::Height);
	gridPosition = Point((window.GetSize().Width - gridSize.Width) / 2, (window.GetSize().Height - gridSize.Height) / 2);
	
	Player::GridPosition = gridPosition;
	
	Square::CreateTextures(renderer);
	
	StartGame();
}

void Snake::StartGame()
{
	player = Player();
	food = Point(rand() % GRID_WIDTH_IN_SQUARES, rand() % GRID_HEIGHT_IN_SQUARES);
	
	nextUpdate = system.GetTicks() + updateDelay;
	running = true;
}

void Snake::Run()
{
	while (running) {
		system.PollEvent();
		
		auto events = system.Events;
		
		for (auto e : events) {
			switch (e.GetType()) {
					
				case Event::Type::QUIT:
					running = false;
					break;
					
				case Event::Type::KEY_DOWN:
				{
					auto kbe = (const KeyboardEvent &)e;
					
					switch (kbe.GetScancode()) {
							
						case Scancode::ESCAPE:
							running = false;
							break;
							
						case Scancode::LEFT:
							player.SetDirection(Player::Direction::LEFT);
							break;
							
						case Scancode::RIGHT:
							player.SetDirection(Player::Direction::RIGHT);
							break;
							
						case Scancode::DOWN:
							player.SetDirection(Player::Direction::DOWN);
							break;
							
						case Scancode::UP:
							player.SetDirection(Player::Direction::UP);
							break;
							
						default:
							// don't care
							break;
					}
					
					break;
				}
					
				default:
					// don't care
					break;
			}
			
			system.Events.clear(); // TODO: find a way of doing this automatically
		}
		
		int now = system.GetTicks();
		if (now >= nextUpdate)
		{
			nextUpdate = now + updateDelay;
			
			player.Update();
			if (player.GetHead() == food) {
				player.Grow(4);
				food = Point(rand() % GRID_WIDTH_IN_SQUARES, rand() % GRID_HEIGHT_IN_SQUARES);
			}
			else if (player.EatsHimself() ||
					 player.GetHead().X < 0 || player.GetHead().X >= GRID_WIDTH_IN_SQUARES || player.GetHead().Y < 0 || player.GetHead().Y >= GRID_HEIGHT_IN_SQUARES)
			{
				StartGame();
			}
		}
		
		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		// Draw the grid
		renderer.SetDrawColor(Color::White);
		renderer.DrawRect(Rect(gridPosition, gridSize));
		
		player.Draw(renderer);
		Square::Draw(renderer, Color::Red, gridPosition + Point(food.X * Square::Width, food.Y * Square::Height));
		
		renderer.Present();
	}
}


