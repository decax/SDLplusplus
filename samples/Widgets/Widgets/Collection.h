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
	
	void AddItem(Picture &picture);
	
	void SetPosition(const SDL::Point &position) override;
	void SetRenderer(SDL::Renderer &renderer) override;
	
	void DrawForeground() override;
	
protected:
	void UpdateItemsPosition();
	
private:
	std::list<Picture *> items;
};
