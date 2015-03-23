#include "Animation.h"

Animation::Frame::Frame(int p_frame, const TimeSpan &p_delay)
: delay(p_delay)
{
	frame = p_frame;
}

void Animation::SetFrames(const std::list<Frame> &p_frames)
{
	frames = p_frames;
	it = frames.begin();
}

void Animation::Update(const Time &time)
{
	if (time.GetTime() >= lastTime+ it->delay)
	{
		if (++it == frames.end())
			it = frames.begin();
		
		lastTime = time.GetTime();
	}
}

int Animation::GetFrame()
{
	return it->frame;
}