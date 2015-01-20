#pragma once

#include <SDLplusplus/SDLplusplus.h>

class Control
{
	friend class GUI;
	
public:
	enum State
	{
		NORMAL, PRESSED
	};

	Control();
	virtual ~Control() {}
	
	virtual void CreateTextures() {}
	
	virtual void Update() {}
	virtual void Draw() {}
	
	virtual void SetRenderer(SDL::Renderer &renderer);
	
	virtual void SetPosition(const SDL::Point &position);
	virtual SDL::Point GetPosition() const;
	
	virtual void SetSize(const SDL::Size &size);
	virtual SDL::Size GetSize() const;
	
	virtual void SetRect(const SDL::Rect &rect);
	virtual SDL::Rect GetRect() const;
	
	bool IsStateNormal() const;
	bool IsStatePressed() const;
	virtual void Press();
	virtual void Release(bool trigger);
	
protected:
	State state;
	SDL::Renderer *renderer;
	
	SDL::Rect rect;
};

inline void Control::SetPosition(const SDL::Point &p_position)
{
	rect.Position = p_position;
}

inline SDL::Point Control::GetPosition() const
{
	return rect.Position;
}

inline void Control::SetSize(const SDL::Size &p_size)
{
	rect.Size = p_size;
}

inline SDL::Size Control::GetSize() const
{
	return rect.Size;
}

inline void Control::SetRect(const SDL::Rect &p_rect)
{
	rect = p_rect;
}

inline SDL::Rect Control::GetRect() const
{
	return rect;
}

inline bool Control::IsStateNormal() const
{
	return state == State::NORMAL;
}

inline bool Control::IsStatePressed() const
{
	return state == State::PRESSED;
}

inline void Control::Press()
{
	state = State::PRESSED;
}

inline void Control::Release(bool trigger)
{
	state = State::NORMAL;
}



