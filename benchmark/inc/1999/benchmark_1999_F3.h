#ifndef BENCHMARK_1999_F3_H
#define BENCHMARK_1999_F3_H

#include "../Benchmarks.h"
class benchmark_1999_F3:public Benchmarks
{
    public:
        benchmark_1999_F3();
        double compute(double* x);
        virtual ~benchmark_1999_F3();

    protected:

    private:
};

#endif // BENCHMARK_1999_F3_H
