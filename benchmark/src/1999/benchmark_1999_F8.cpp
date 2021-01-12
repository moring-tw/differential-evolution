#include "../../inc/1999/benchmark_1999_F8.h"

benchmark_1999_F8::benchmark_1999_F8()
{
    dimension = 30;
    minX = -500;
    maxX = 500;
    ID = 36;
    //ctor
}

benchmark_1999_F8::~benchmark_1999_F8()
{
    //dtor
}

double benchmark_1999_F8::compute(double* x){
    double result = 0.0;
    for(unsigned dim_counter = 0; dim_counter < dimension; dim_counter++){
        result += (0-x[dim_counter])*sin(sqrt(fabs(x[dim_counter])));
    }
    update(result);
    return result;
}
