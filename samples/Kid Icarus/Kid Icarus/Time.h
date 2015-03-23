#pragma once

#include <stdint.h>

class TimeSpan
{
public:
	TimeSpan();
	TimeSpan(uint32_t millisec);
	
	void Update();
	
	bool operator ==(const TimeSpan &time) const;
	bool operator !=(const TimeSpan &time) const;
	bool operator >(const TimeSpan &time) const;
	bool operator >=(const TimeSpan &time) const;
	bool operator <(const TimeSpan &time) const;
	bool operator <=(const TimeSpan &time) const;
	
	TimeSpan operator +(const TimeSpan &time) const;
	TimeSpan operator -(const TimeSpan &time) const;
	
	float GetTotalSeconds() const;
	uint32_t GetTotalMilliseconds() const;
	
private:
	uint32_t millisec;
};

inline TimeSpan::TimeSpan()
{
	millisec = 0;
}

inline TimeSpan::TimeSpan(uint32_t p_millisec)
{
	millisec = p_millisec;
}

inline bool TimeSpan::operator ==(const TimeSpan &time) const
{
	return millisec == time.millisec;
}

inline bool TimeSpan::operator !=(const TimeSpan &time) const
{
	return millisec != time.millisec;
}

inline bool TimeSpan::operator >(const TimeSpan &time) const
{
	return millisec > time.millisec;
}

inline bool TimeSpan::operator >=(const TimeSpan &time) const
{
	return millisec >= time.millisec;
}

inline bool TimeSpan::operator <(const TimeSpan &time) const
{
	return millisec < time.millisec;
}

inline bool TimeSpan::operator <=(const TimeSpan &time) const
{
	return millisec <= time.millisec;
}

inline TimeSpan TimeSpan::operator +(const TimeSpan &p_time) const
{
	return TimeSpan(millisec + p_time.millisec);
}

inline TimeSpan TimeSpan::operator -(const TimeSpan &p_time) const
{
	return TimeSpan(millisec - p_time.millisec);
}

inline float TimeSpan::GetTotalSeconds() const
{
	return millisec / 1000.0f;
}

inline uint32_t TimeSpan::GetTotalMilliseconds() const
{
	return millisec;
}

class Time
{
public:
	TimeSpan GetTime() const;
	TimeSpan GetDelta() const;
	
	void Update();
	
private:
	TimeSpan now;
	TimeSpan previous;
};

inline TimeSpan Time::GetTime() const
{
	return now;
}

inline TimeSpan Time::GetDelta() const
{
	return now - previous;
}