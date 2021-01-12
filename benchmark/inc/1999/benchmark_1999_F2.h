#ifndef BENCHMARK_1999_F2_H
#define BENCHMARK_1999_F2_H

#include "..\Benchmarks.h"
class benchmark_1999_F2:public Benchmarks
{
    public:
        benchmark_1999_F2();
        double compute(double* x);
        virtual ~benchmark_1999_F2();

    protected:

    private:
};

#endif // BENCHMARK_1999_F2_H
