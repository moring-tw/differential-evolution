#include "../../inc/SADE_2009/benchmark_2009_sade_f12.h"

Benchmark_2009_Sade_F12::Benchmark_2009_Sade_F12()
{
    //ctor
}

Benchmark_2009_Sade_F12::~Benchmark_2009_Sade_F12()
{
    //dtor
}

Benchmark_2009_Sade_F12::Benchmark_2009_Sade_F12(unsigned dimension, double minX, double maxX, unsigned ID){
    Benchmarks::dimension = dimension;
    Benchmarks::ID = ID;
    Benchmarks::minX = minX;
    Benchmarks::maxX = maxX;
}

double Benchmark_2009_Sade_F12::compute(double* x){
    double result = 418.9829 * Benchmarks::dimension;
    for(unsigned dim_counter = 0; dim_counter < Benchmarks::dimension; dim_counter++){
        result -= x[dim_counter] * sin(sqrt(fabs(x[dim_counter])));
    }
    return result;
}
