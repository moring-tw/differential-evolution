#include "../../inc/1999/benchmark_1999_F7.h"

benchmark_1999_F7::benchmark_1999_F7()
{
    dimension = 30;
    minX = -1.28;
    maxX = 1.28;
    ID = 35;

    //ctor
}

benchmark_1999_F7::~benchmark_1999_F7()
{
    //dtor
}

double random(double _max, double _min){//res = [_min, _max)
    return (_max - _min) * rand() / (RAND_MAX + 1.0) + _min;
}

double benchmark_1999_F7::compute(double* x){
    double result = 0.0;
    for(unsigned dim_counter = 0; dim_counter < dimension; dim_counter++){
        result += (dim_counter+1) * pow(x[dim_counter],4) ;
    }
    result += random(1,0);
    return result;
}
