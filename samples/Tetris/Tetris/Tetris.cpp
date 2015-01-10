#include "Tetris.h"

#include <iostream>
#include <exception>

#include "Piece.h"
#include "Square.h"

#include <SDLplusplus/Image.h>

using namespace std;
using namespace SDL;

Tetris::Tetris()
: system(System::SubSystem::EVERYTHING),
  window("tetris", Size(800, 600)),
  renderer(window, Renderer::TypeFlag::ACCELERATED | Renderer::TypeFlag::PRESENT_VSYNC)
{
	srand((unsigned int)time(nullptr));
	
	gridSizeInSquares = Size(GRID_WIDTH_IN_SQUARES, GRID_HEIGHT_IN_SQUARES);
	
	gridSize = Size(gridSizeInSquares.Width * Square::Width, gridSizeInSquares.Height * Square::Height);
	gridPosition = Point((window.GetSize().Width - gridSize.Width) / 2, (window.GetSize().Height - gridSize.Height) / 2);
	
	Square::CreateTextures(renderer);
	
	Piece::GridPosition = gridPosition;
	
	StartGame();
}

void Tetris::StartGame()
{
	memset(grid, 0, sizeof(grid));
	
	piece = GetNextPiece();
	piece->Position = Point(gridSizeInSquares.Width / 2, 0);

	nextPiece = GetNextPiece();

	nextUpdate = system.GetTicks() + updateDelay;
	running = true;
}

void Tetris::Run()
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
							if (piece->Position.X > 0 && !piece->Collide(grid, piece->Position - Point(1, 0))) {
								piece->Position.X--;
							}
							break;
							
						case Scancode::RIGHT:
							if (piece->Position.X + piece->GetBounds().Size.Width < gridSizeInSquares.Width && // fixme: bounds should have y2 instead of width
								!piece->Collide(grid, piece->Position + Point(1, 0))) {
								piece->Position.X++;
							}
							break;
							
						case Scancode::DOWN:
							MovePieceDown();
							break;
							
						case Scancode::UP:
							piece->Rotate();
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
			
			MovePieceDown();
		}
		
		CheckForCompleteLine();
		
		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		// Draw the grid
		renderer.SetDrawColor(Color::White);
		renderer.DrawLine(gridPosition - Point(1, 0),                gridPosition + Point(-1, gridSize.Height));
		renderer.DrawLine(gridPosition + Point(gridSize.Width, 0),   gridPosition + Point(gridSize.Width, gridSize.Height));
		renderer.DrawLine(gridPosition + Point(-1, gridSize.Height), gridPosition + Point(gridSize.Width, gridSize.Height));
		
		piece->Draw(renderer);
		nextPiece->Draw(renderer);
		
		// Draw deactivated pieces
		for (int x = 0; x < gridSizeInSquares.Width; x++) {
			for (int y = 0; y < gridSizeInSquares.Height; y++) {
				if (grid[x][y]) {
					Square::Draw(renderer, SDL::Color::Gray, gridPosition + Point(x * Square::Width, y * Square::Height));
				}
			}
		}
		
		font.RenderTextBlended(renderer, "salut", Point(0, 0));
		
		renderer.Present();
	}
}

Piece *Tetris::GetNextPiece()
{
	auto piece = new Piece((Piece::Shape)(rand() % Piece::NB_SHAPES));
	piece->Position = SDL::Point(gridSizeInSquares.Width + 2, 1);
	
	return piece;
}

void Tetris::MovePieceDown()
{
	if (piece->Position.Y + piece->GetBounds().Size.Height < gridSizeInSquares.Height &&
		!piece->Collide(grid, piece->Position + SDL::Point(0, 1))) {
		piece->Position.Y++;
	}
	else
	{
		piece->Deactivate(grid);
		piece = nextPiece;
		piece->Position = SDL::Point(gridSizeInSquares.Width / 2, 0);
		nextPiece = GetNextPiece();
	}
}

void Tetris::CheckForCompleteLine()
{
	// Check for complete line
	for (int y = 0; y < gridSizeInSquares.Height; y++) {
		bool lineComplete = true;
		
		for (int x = 0; x < gridSizeInSquares.Width; x++) {
			if (!grid[x][y]) {
				lineComplete = false;
			}
		}
		
		if (lineComplete) {
			// Drop all blocks above from 1
			for (int y2 = y; y2 > 0; y2--) {
				for (int x = 0; x < gridSizeInSquares.Width; x++) {
					grid[x][y2] = grid[x][y2 -1 ];
				}
			}
			
			// Empty first line
			for (int x = 0; x < gridSizeInSquares.Width; x++) {
				grid[x][0] = false;
			}
		}
	}
}

