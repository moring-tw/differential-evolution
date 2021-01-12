#ifndef BENCHMARK_2009_SADE_F12_H
#define BENCHMARK_2009_SADE_F12_H
#include "../Benchmarks.h"


class Benchmark_2009_Sade_F12:public Benchmarks
{
    public:
        Benchmark_2009_Sade_F12();
        Benchmark_2009_Sade_F12(unsigned,double,double,unsigned);
        double compute(double*);
        virtual ~Benchmark_2009_Sade_F12();

    protected:

    private:
};

#endif // BENCHMARK_2009_SADE_F12_H
