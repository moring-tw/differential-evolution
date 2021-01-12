#ifndef BENCHMARK_1999_F7_H
#define BENCHMARK_1999_F7_H

#include "../Benchmarks.h"
class benchmark_1999_F7:public Benchmarks
{
    public:
        benchmark_1999_F7();
        double compute(double*);
        virtual ~benchmark_1999_F7();

    protected:

    private:
};

#endif // BENCHMARK_1999_F7_H
