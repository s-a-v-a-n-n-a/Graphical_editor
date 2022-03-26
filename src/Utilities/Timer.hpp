#ifndef TIMER_H 
#define TIMER_H

#include <ctime>
#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point start_time;

public:
	Timer()
	: start_time()
	{
		start_time = std::chrono::steady_clock::now();
	}

	size_t get_passed_time()
	{
		std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
		std::chrono::steady_clock::duration time_span = current_time - start_time;
		auto dtime = std::chrono::duration_cast<std::chrono::microseconds>(time_span);
		return dtime.count();
	}
};

#endif // TIMER_H
