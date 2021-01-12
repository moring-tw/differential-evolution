#include "../../inc/SADE_2009/benchmark_2009_sade_f3.h"

Benchmark_2009_Sade_F3::Benchmark_2009_Sade_F3()
{
    //ctor
}

Benchmark_2009_Sade_F3::Benchmark_2009_Sade_F3(unsigned dimension, double minX, double maxX, unsigned ID)
{
    //ctor
    Benchmark_2009_Sade_F3::dimension = dimension;
    Benchmark_2009_Sade_F3::ID = ID;
    Benchmark_2009_Sade_F3::minX = minX;
    Benchmark_2009_Sade_F3::maxX = maxX;
}

Benchmark_2009_Sade_F3::~Benchmark_2009_Sade_F3()
{
    //dtor
}

double Benchmark_2009_Sade_F3::compute(double* x){
    double result = 0;
    for(unsigned dim_counter = 0; dim_counter < Benchmark_2009_Sade_F3::dimension-1; dim_counter++){
        result += 100*pow((pow(x[dim_counter],2)-x[dim_counter+1]),2)+pow((x[dim_counter]-1),2);
    }
    return result;
}
