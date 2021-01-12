#include "../../inc/1999/benchmark_1999_F5.h"

benchmark_1999_F5::benchmark_1999_F5()
{
    //ctor
    dimension = 30;
    minX = -30.0;
    maxX = 30.0;
    ID = 33;
}

benchmark_1999_F5::~benchmark_1999_F5()
{
    //dtor
}
double benchmark_1999_F5::compute(double* x){
    double result = 0.0;
    for(unsigned dim_counter = 0; dim_counter < dimension-1; dim_counter++){
        result += 100*pow(x[dim_counter+1]-pow(x[dim_counter],2),2)+pow(x[dim_counter]-1,2);
    }
    //update(result);
    return result;
}
