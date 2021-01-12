#ifndef BENCHMARK_1999_F6_H
#define BENCHMARK_1999_F6_H

#include "../Benchmarks.h"
class benchmark_1999_F6:public Benchmarks
{
    public:
        benchmark_1999_F6();
        double compute(double*);
        virtual ~benchmark_1999_F6();

    protected:

    private:
};

#endif // BENCHMARK_1999_F6_H
