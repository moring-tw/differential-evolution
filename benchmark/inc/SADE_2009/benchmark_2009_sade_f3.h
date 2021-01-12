#ifndef BENCHMARK_2009_SADE_F3_H
#define BENCHMARK_2009_SADE_F3_H
#include "../Benchmarks.h"


class Benchmark_2009_Sade_F3:public Benchmarks
{
    public:
        Benchmark_2009_Sade_F3();
        Benchmark_2009_Sade_F3(unsigned,double,double,unsigned);
        virtual ~Benchmark_2009_Sade_F3();
        double compute(double*);

    protected:

    private:
};

#endif // BENCHMARK_2009_SADE_F3_H
