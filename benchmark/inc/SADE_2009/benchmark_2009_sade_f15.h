#ifndef BENCHMARK_2009_SADE_F15_H
#define BENCHMARK_2009_SADE_F15_H
#include "../Benchmarks.h"

class Benchmark_2009_Sade_F15:public Benchmarks
{
    public:
        Benchmark_2009_Sade_F15();
        Benchmark_2009_Sade_F15(unsigned,double,double,unsigned);
        virtual ~Benchmark_2009_Sade_F15();
        double compute(double*);

    protected:

    private:
};

#endif // BENCHMARK_2009_SADE_F15_H
