#include "../../inc/1999/benchmark_1999_F2.h"

benchmark_1999_F2::benchmark_1999_F2()
{
    //ctor
    dimension = 30;
    minX = -10.0;
    maxX = 10.0;
    ID = 30;
}

benchmark_1999_F2::~benchmark_1999_F2()
{
    //dtor
}

double benchmark_1999_F2::compute(double *x){
    double result = 0.0;
    double temp = 1.0;
    for(int dim_counter = 0; dim_counter < dimension; dim_counter++){
        result += fabs(x[dim_counter]);
        temp *= fabs(x[dim_counter]);
    }
    result += temp;
    update(result);
    return result;
    //return result;
}
