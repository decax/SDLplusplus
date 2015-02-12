#pragma once

#include "Control.h"

#include <SDLplusplus/SDLplusplus.h>

class List : public Control
{
public:
	~List();
	
	void SetRenderer(SDL::Renderer &renderer) override;
	
	void AddCellLabel(std::string text);
	
	void SetPosition(const SDL::Point &position) override;
	
	void DrawForeground() override;
	
private:
	std::list<Control *> cells;
	
	void UpdateCellsPosition();
};
