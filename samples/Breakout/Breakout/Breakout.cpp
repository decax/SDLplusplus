#include "Breakout.h"

#include "Square.h"
#include "Collider.h"
#include "Direction.h"

#include <iostream>
#include <exception>

using namespace std;
using namespace SDL;

Breakout::Breakout()
: system(System::SubSystem::EVERYTHING),
  window("Breakout", Size(800, 600)),
  renderer(window, Renderer::TypeFlag::ACCELERATED | Renderer::TypeFlag::PRESENT_VSYNC),
  player(renderer),
  ball(renderer)
{
	srand((unsigned int)time(nullptr));
	
	system.RegisterEvent(Event::QUIT,     [&](const Event &) { running = false; });
	system.RegisterEvent(Event::KEY_DOWN, bind(&Breakout::OnKeyDown, this, placeholders::_1));
	
	gridSizeInSquares = Size(GRID_WIDTH_IN_BLOCKS, GRID_HEIGHT_IN_BLOCKS);
	
	gridSize = Size(gridSizeInSquares.Width * Block::Width, gridSizeInSquares.Height * Block::Height);
	gridPosition = Point((window.GetSize().Width - gridSize.Width) / 2, (window.GetSize().Height - gridSize.Height) / 2);
	
	Player::GridPosition = gridPosition;
	Block::GridPosition  = gridPosition;
	Ball::GridRect       = Rect(gridPosition, gridSize);
	
	Block::CreateTexture(renderer);
	Square::CreateTextures(renderer);
	
	StartGame();
}

void Breakout::StartGame()
{
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < GRID_WIDTH_IN_BLOCKS; x++) {
			blocks.push_back(Block(Point(x * Block::Width, y * Block::Height), (x + y) % 2 ? Color::Red : Color::Green));
		}
	}

	player.SetPosition(Point((gridSize / 2).Width, gridSize.Height - Player::Height * 2));
	ball.SetPosition(Point((gridSize / 2).Height, gridSize.Height - 50));
	
	lastTime = system.GetTicks();
	nextUpdate = system.GetTicks() + updateDelay;
	running = true;
}

void Breakout::OnKeyDown(const Event &event)
{
	auto kbe = (const KeyboardEvent &)event;
	
	switch (kbe.GetScancode()) {
			
		case Scancode::ESCAPE:
			running = false;
			break;
			
		case Scancode::LEFT:
			player.SetDirection(kbe.GetState() == KeyboardEvent::State::PRESSED ? Direction::LEFT : Direction::NONE);
			break;
			
		case Scancode::RIGHT:
			player.SetDirection(kbe.GetState() == KeyboardEvent::State::PRESSED ? Direction::RIGHT : Direction::NONE);
			break;
			
		default:
			// don't care
			break;
	}
}

void Breakout::Run()
{
	while (running) {
		system.Update();
		
		// Update
		{
			int now = system.GetTicks();
			float deltaTime = (now - lastTime) / 1000.0f;
			lastTime = now;
			ball.Update(deltaTime);
			player.Update(deltaTime);
			
			// build a list of colliders
			std::list<Collider *> colliders;
			for (auto &block : blocks) {
				colliders.push_back(&block);
			}
			
			// Check for collisions with every object and adjust the ball position accordingly
			ball.Collide(colliders);
		}
		
		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		// Draw the grid
		renderer.SetDrawColor(Color::White);
		renderer.DrawRect(Rect(gridPosition, gridSize));
		
		for (auto it = blocks.begin(); it != blocks.end(); ) {
			if ((*it).IsDead()) {
				blocks.erase(it++);
			}
			else {
				(*it).Draw(renderer);
				++it;
			}
		}
		
		player.Draw(renderer);
		ball.Draw(renderer);
		
		renderer.Present();
	}
}


