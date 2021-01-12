#include "../../inc/SADE_2009/benchmark_2009_sade_f15.h"

Benchmark_2009_Sade_F15::Benchmark_2009_Sade_F15()
{
    //ctor
}

Benchmark_2009_Sade_F15::Benchmark_2009_Sade_F15(unsigned dimension, double minX, double maxX, unsigned ID)
{
    //ctor
    Benchmarks::dimension = dimension;
    Benchmarks::ID = ID;
    Benchmarks::minX = minX;
    Benchmarks::maxX = maxX;
}

Benchmark_2009_Sade_F15::~Benchmark_2009_Sade_F15()
{
    //dtor
}

double Benchmark_2009_Sade_F15::compute(double* x){
    double result = 0, temp = 1;
    for(int dim_counter = 0; dim_counter < Benchmarks::dimension; dim_counter++){
        result += fabs(x[dim_counter]);
        temp *= fabs(x[dim_counter]);
    }
    return result + temp;
}
