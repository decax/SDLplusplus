#pragma once

#include "Control.h"
#include "Scrollbar.h"

#include <SDLplusplus/SDLplusplus.h>

#include <list>

class Collection : public Control
{
public:
	Collection();
	~Collection();
	
	void AddItem(Control &control);
	
	void SetPosition(const SDL::Point &position) override;
	void SetSize(const SDL::Size &size) override;
	void SetRenderer(SDL::Renderer &renderer) override;
	
	void Scroll(const SDL::Size &size) override;
	
	void DrawForeground() override;
	
protected:
	void UpdateItemsPosition();
	
private:
	SDL::Point contentPosition;
	SDL::Size contentSize;
	
	SDL::Size offset;
	
	Scrollbar scrollbar;
	std::list<Control *> items;
};
