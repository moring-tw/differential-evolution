#ifndef BENCHMARK_2009_SADE_F16_H
#define BENCHMARK_2009_SADE_F16_H
#include "../Benchmarks.h"


class Benchmark_2009_Sade_F16:public Benchmarks
{
    public:
        Benchmark_2009_Sade_F16();
        Benchmark_2009_Sade_F16(unsigned,double,double,unsigned);
        virtual ~Benchmark_2009_Sade_F16();
        double compute(double*);

    protected:

    private:
};

#endif // BENCHMARK_2009_SADE_F16_H
