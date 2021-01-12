#include "../../inc/1999/benchmark_1999_F6.h"

benchmark_1999_F6::benchmark_1999_F6()
{
    //ctor
    dimension = 30;
    minX = -100.0;
    maxX = 100.0;
    ID = 34;
}

benchmark_1999_F6::~benchmark_1999_F6()
{
    //dtor
}
double benchmark_1999_F6::compute(double* x){
    double result = 0.0;
    for(unsigned dim_counter = 0; dim_counter < dimension; dim_counter++){
        result += pow(floor(x[dim_counter]+0.5),2);
    }
    return result;
}
