#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <sys/time.h>

class Timer {
	private:
		struct timeval t0;	// start time
		struct timeval t1;	// actual time
	
	public:
		Timer();
		void Restart();
		double Delta();
};

#endif
