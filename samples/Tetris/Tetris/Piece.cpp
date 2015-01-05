#include "Piece.h"

#include "Square.h"

using namespace SDL;

Point Piece::GridPosition;

const SDL::Color *Piece::colors[Piece::NB_SHAPES] =
{
	&Color::Magenta, &Color::White, &Color::Brown, &Color::Cyan, &Color::Green, &Color::Red, &Color::Blue
};

int Piece::shapeMasks[Piece::NB_SHAPES][4][Piece::bufferHeight][Piece::bufferWidth] =
{
	// L
	{
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		{
			{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		
		{
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},

	// J
	{
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		{
			{ 1, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		{
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},

	// T
	{
		{
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},

	// Z
	{
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	
	// S
	{
		{
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	
	// I
	{
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
		},
		{
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
		},
		{
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},

	// O
	{
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
};

Piece::Piece(Shape p_shape)
{
	shape = p_shape;
	rotation = 0;

	UpdateShapeMask();
}

void Piece::UpdateShapeMask()
{
	memset(buffer, 0, sizeof(buffer));

	for (int x = 0; x < bufferWidth; x++) {
		for (int y = 0; y < bufferHeight; y++) {
			buffer[x][y] = shapeMasks[shape][rotation][y][x];
		}
	}
}

// Return the bounds of the piece ((pos.x, pos.y, pos.x + width, pos.y + height)
// This checks for empty "squares"
SDL::Rect Piece::GetBounds() const
{
	Rect rect(Position, Size(1, 1));
	
	// find rightmost piece
	for (int y = 0; y < bufferHeight; y++) {
		for (int x = 0; x < bufferWidth; x++) {
			if (buffer[x][y] && x > (rect.Size.Width - 1)) {
				rect.Size.Width = x + 1;
			}
		}
	}

	// find downmost piece de ta mere
	for (int x = 0; x < bufferWidth; x++) {
		for (int y = 0; y < bufferHeight; y++) {
			if (buffer[x][y] && y > (rect.Size.Height - 1)) {
				rect.Size.Height = y + 1;
			}
		}
	}
	
	return rect;
}

void Piece::Rotate()
{
	rotation++;
	rotation %= 4;
	
	UpdateShapeMask();
}

bool Piece::Collide(bool grid[10][17], SDL::Point position) const
{
	for (int x = 0; x < bufferWidth; x++) {
		for (int y = 0; y < bufferHeight; y++) {
			if (buffer[x][y] && grid[position.X + x][position.Y + y]) {
				return true;
			}
		}
	}
	
	return false;
}

void Piece::Deactivate(bool grid[10][17])
{
	for (int x = 0; x < bufferWidth; x++) {
		for (int y = 0; y < bufferHeight; y++) {
			if (buffer[x][y]) {
				grid[Position.X + x][Position.Y + y] = true;
			}
		}
	}
}

void Piece::Draw(Renderer &p_renderer)
{
	for (int x = 0; x < bufferWidth; x++) {
		for (int y = 0; y < bufferHeight; y++) {
			if (buffer[x][y]) {
				Square::Draw(p_renderer, *colors[shape], GridPosition + Point((Position.X + x) * Square::Width, (Position.Y + y) * Square::Height));
			}
		}
	}
}
