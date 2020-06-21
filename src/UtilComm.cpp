#include "UtilComm.hpp"


Timer::Timer() {
	gettimeofday(&t0, 0);
}

void Timer::Restart() {
	gettimeofday(&t0, 0);
}
double Timer::Delta() {
	gettimeofday(&t1, 0);
	double diff = (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;

	return diff;
}


arma::fmat bezier_(arma:: fmat GH, float t)
{
    arma::frowvec T = {powf(t,3),powf(t,2),t,1.0};
    arma :: fmat Qt  = T * MH_() * GH;
    return Qt;
}


arma::fmat MH_()
{
/******************************
funcion para obtener los puntos de bezier
*********************************************/
arma::fmat MH = {{-1.0, 3.0, -3.0, 1.0},
                     {3.0, -6.0, 3.0, 0.0},
                     {-3.0, 3.0, 0.0, 0.0},
                     {1.0, 0.0, 0.0, 0.0}
                     };

					 return MH;

}

/******************************************************
 *  other
 * *****************************************************/
//for "debuging".
void print_D(std::string printing)
{
    std::cout<<std::endl<< printing << std::endl;
}