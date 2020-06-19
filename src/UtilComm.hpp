#ifndef UTIL_COMMON
#define UTIL_COMMON


#include <time.h>
#include <chrono>
#include <sys/time.h>
#include<armadillo>

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


/******************************
funcion para obtener los puntos de bezier
*********************************************/
arma::fmat MH = {{-1.0, 3.0, -3.0, 1.0},
                     {3.0, -6.0, 3.0, 0.0},
                     {-3.0, 3.0, 0.0, 0.0},
                     {1.0, 0.0, 0.0, 0.0}
                     };

arma::fmat bezier(arma:: fmat GH, float t);



#endif
