#include "../../inc/1999/benchmark_1999_F1.h"

benchmark_1999_F1::benchmark_1999_F1()
{
    dimension = 30;
    minX = -100.0;
    maxX = 100.0;
    ID = 29;
    //ctor
}

benchmark_1999_F1::~benchmark_1999_F1()
{
    //dtor
}

double benchmark_1999_F1::compute(double *x){
    double result = 0.0;
    for(int dim_counter = 0; dim_counter < dimension; dim_counter++){
        result += pow(x[dim_counter],2);
    }
    update(result);
    //return sphere(x,30);
    return result;
}
