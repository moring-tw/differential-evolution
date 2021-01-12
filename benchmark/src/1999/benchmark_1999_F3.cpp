#include "../../inc/1999/benchmark_1999_F3.h"

benchmark_1999_F3::benchmark_1999_F3()
{
    dimension = 30;
    minX = -100.0;
    maxX = 100.0;
    ID = 31;
    //ctor
}

benchmark_1999_F3::~benchmark_1999_F3()
{
    //dtor
}
double benchmark_1999_F3::compute(double *x){
    double temp = 0.0;
    double result = 0.0;
    for(int dim_counter = 0; dim_counter < dimension; dim_counter++){
        temp = 0.0;
        for(unsigned dim_counter2 = 0; dim_counter2 <= dim_counter; dim_counter2++){
            temp += x[dim_counter2];
        }
        result += pow(temp,2);
    }
    update(result);
    //return sphere(x,30);
    return result;
}
