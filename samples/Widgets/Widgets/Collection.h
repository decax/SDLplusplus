#pragma once

#include "Control.h"
#include "Picture.h"

#include <SDLplusplus/SDLplusplus.h>

#include <list>

class Collection : public Control
{
public:
	Collection();
	~Collection();
	
	void AddItem(Control &control);
	
	void SetPosition(const SDL::Point &position) override;
	void SetRenderer(SDL::Renderer &renderer) override;
	
	void Scroll(const SDL::Size &size) override;
	
	void DrawForeground() override;
	
protected:
	void UpdateItemsPosition();
	
private:
	SDL::Point contentPosition;
	
	SDL::Size offset;
	
	std::list<Control *> items;
};
