#include "Player.h"

#include "Square.h"

using namespace SDL;

Point Player::GridPosition;

Player::Player()
{
	body.push_back(Point(3, 0));
	body.push_back(Point(2, 0));
	body.push_back(Point(1, 0));
	body.push_back(Point(0, 0));

	direction = Direction::RIGHT;
	
	toGrow = 0;
}

void Player::Update()
{
	auto it = body.begin();
	auto previous = *it;
	
	switch (direction) {
		case Direction::UP:    *it += Point( 0, -1); break;
		case Direction::DOWN:  *it += Point( 0,  1); break;
		case Direction::LEFT:  *it += Point(-1,  0); break;
		case Direction::RIGHT: *it += Point( 1,  0); break;
	}
	
	++it;
	
	for (; it != body.end(); ++it) {
		std::swap(*it, previous);
	}
	
	if (toGrow > 0) {
		body.push_back(previous);
		toGrow--;
	}
}

void Player::Draw(Renderer &p_renderer)
{
	for (auto position : body) {
		Square::Draw(p_renderer, Color::Blue, GridPosition + Point(position.X * Square::Width, position.Y * Square::Height));
	}
}

void Player::SetDirection(Direction p_direction)
{
	direction = p_direction;
}

Point Player::GetHead() const
{
	return *body.begin();
}

void Player::Grow(int p_size)
{
	toGrow += p_size;
}

bool Player::EatsHimself() const
{
	auto it = body.begin();
	++it;
	for (; it != body.end(); ++it) {
		if (*it == GetHead()) {
			return true;
		}
	}

	return false;
}

