#pragma once

#include <SDLplusplus/SDLplusplus.h>

class Control
{
	friend class GUI;
	
public:
	Control();
	virtual ~Control() {}
	
	virtual void SetPosition(const SDL::Point &position);
	virtual SDL::Point GetPosition() const;
	
	const SDL::Rect &GetRect() const;
	
	virtual void Update() {}
	virtual void Draw();
	
	virtual void CreateTextures() {}
	virtual void SetRenderer(SDL::Renderer &renderer);
	
	virtual void Hover(bool hovered) {}
	virtual void Press() {}
	virtual void Release(bool clicked = true) {}
	
	SDL::Color backgroundColor;
	SDL::Color color;

protected:
	virtual void DrawBackground();
	virtual void DrawForeground();
	
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

inline const SDL::Rect &Control::GetRect() const
{
	return rect;
}