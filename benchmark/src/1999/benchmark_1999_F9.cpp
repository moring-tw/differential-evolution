#include "../../inc/1999/benchmark_1999_F9.h"
#define PI (3.141592653589793238462643383279)
benchmark_1999_F9::benchmark_1999_F9()
{
    //ctor
    dimension = 30;
    minX = -5.12;
    maxX = 5.12;
    ID = 37;
}

benchmark_1999_F9::~benchmark_1999_F9()
{
    //dtor
}

double benchmark_1999_F9::compute(double* x){
    double result = 0.0;
    for(unsigned dim_counter = 0; dim_counter < dimension; dim_counter ++){
        result += pow(x[dim_counter],2)-10*cos(2*PI*x[dim_counter])+10;
    }

    return result;
}
