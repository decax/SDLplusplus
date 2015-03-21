#pragma once

#include "Control.h"

#include <SDLplusplus/SDLplusplus.h>

class Scrollbar : public Control
{
public:
	Scrollbar();
	
	void DrawForeground() override;
	
	SDL::Size contentSize;
	
	void SetHandleSize(float size);
	float GetValue() const;
	
private:
	float handleSize;
	float value;
};