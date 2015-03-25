#include "Animation.h"

#include <vector>
#include <istream>
#include <sstream>
#include <iostream>

using namespace std;

Animation::Frame::Frame(int p_index, const TimeSpan &p_delay)
: delay(p_delay)
{
	index = p_index;
}

void Animation::SetFrames(const std::string &script)
{
	istringstream iss(script);
	
	// Split the string in tokens (separated by " ")
	vector<string> tokens { istream_iterator<string>{iss}, istream_iterator<string>{} };
	
	string prefix("Delay:");
	
	Frame frame;
	frame.delay = 0;
	
	// Fixme: should probably be safer...
	for (auto token : tokens) {
		if (token.compare(0, prefix.size(), prefix) == 0) {
			frame.delay = atoi(token.substr(prefix.size()).c_str());
		}
		else {
			frame.index = atoi(token.c_str());
			
			frames.push_back(frame);
		}
	}
	
	it = frames.begin();
}

void Animation::SetFrames(const std::list<Frame> &p_frames)
{
	frames = p_frames;
	it = frames.begin();
}

void Animation::Update(const Time &time)
{
	if (time.GetTime() >= lastTime + it->delay)
	{
		if (++it == frames.end())
			it = frames.begin();
		
		lastTime = time.GetTime();
	}
}

const Animation::Frame &Animation::GetFrame()
{
	return *it;
}

string Animation::ToString() const
{
	char tmp[1024];
	string s;
	
	for (auto frame : frames) {
		sprintf(tmp, "%d (%d)", frame.index, frame.delay.GetTotalMilliseconds());
		s += tmp;
	}
	return s;
}