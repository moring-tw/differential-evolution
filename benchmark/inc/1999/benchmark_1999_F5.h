#ifndef BENCHMARK_1999_F5_H
#define BENCHMARK_1999_F5_H

#include "../Benchmarks.h"
class benchmark_1999_F5:public Benchmarks
{
    public:
        benchmark_1999_F5();
        double compute(double*);
        virtual ~benchmark_1999_F5();

    protected:

    private:
};

#endif // BENCHMARK_1999_F5_H
