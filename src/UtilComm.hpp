#ifndef UTIL_COMMON
#define UTIL_COMMON


#include <time.h>
#include <chrono>
#include <sys/time.h>
#include <armadillo>

#define PI 3.14159265358979


class Timer {
	private:
		struct timeval t0;	// start time
		struct timeval t1;	// actual time
	
	public:
		Timer();
		void Restart();
		double Delta();
};


arma::fmat MH_();
arma::fmat bezier_(arma:: fmat GH, float t);



#endif
