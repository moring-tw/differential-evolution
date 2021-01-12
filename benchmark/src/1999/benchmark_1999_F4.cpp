#include "../../inc/1999/benchmark_1999_F4.h"

benchmark_1999_F4::benchmark_1999_F4()
{
    dimension = 30;
    minX = -100.0;
    maxX = 100.0;
    ID = 32;
    //ctor
}

benchmark_1999_F4::~benchmark_1999_F4()
{
    //dtor
}
double benchmark_1999_F4::compute(double *x){
    double result = 0.0;
    for(int dim_counter = 0 ; dim_counter < dimension; dim_counter++){
        if(fabs(x[dim_counter])>result) result = fabs(x[dim_counter]);
    }
    update(result);
    return result;
}
