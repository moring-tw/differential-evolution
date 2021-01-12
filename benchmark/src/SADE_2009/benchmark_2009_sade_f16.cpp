#include "../../inc/SADE_2009/benchmark_2009_sade_f16.h"

Benchmark_2009_Sade_F16::Benchmark_2009_Sade_F16()
{
    //ctor
}

Benchmark_2009_Sade_F16::Benchmark_2009_Sade_F16(unsigned dimension, double minX, double maxX, unsigned ID)
{
    //ctor
    Benchmarks::dimension = dimension;
    Benchmarks::ID = ID;
    Benchmarks::minX = minX;
    Benchmarks::maxX = maxX;
}

Benchmark_2009_Sade_F16::~Benchmark_2009_Sade_F16()
{
    //dtor
}

double Benchmark_2009_Sade_F16::compute(double* x){
    double result = 0;
    for(unsigned dim_counter = 0; dim_counter < Benchmarks::dimension; dim_counter++){
        if(fabs(x[dim_counter]) > result) result = fabs(x[dim_counter]);
    }
    return result;
}
