#pragma once

#include "Time.h"

#include <list>

class Animation
{
public:
	class Frame
	{
	public:
		Frame(int frame, const TimeSpan &delay);
		
		int frame;
		TimeSpan delay;
	};
	
	void SetFrames(const std::list<Frame> &frames);
	
	void Update(const Time &time);
	int GetFrame();
	
private:
	std::list<Frame> frames;
	std::list<Frame>::iterator it;
	
	TimeSpan lastTime;
};