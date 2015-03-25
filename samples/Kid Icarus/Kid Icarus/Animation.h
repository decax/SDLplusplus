#pragma once

#include "Time.h"

#include <list>
#include <string>

class Animation
{
public:
	class Frame
	{
	public:
		Frame() {}
		Frame(int index, const TimeSpan &delay);
		
		int index;
		TimeSpan delay;
	};
	
	void SetFrames(const std::string &script);
	void SetFrames(const std::list<Frame> &frames);
	
	void Update(const Time &time);
	const Frame &GetFrame();
	
	std::string ToString() const;
	
private:
	std::list<Frame> frames;
	std::list<Frame>::iterator it;
	
	TimeSpan lastTime;
};