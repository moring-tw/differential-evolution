#ifndef BENCHMARK_1999_F4_H
#define BENCHMARK_1999_F4_H

#include "../benchmarks.h"
class benchmark_1999_F4:public Benchmarks
{
    public:
        benchmark_1999_F4();
        double compute(double*);
        virtual ~benchmark_1999_F4();

    protected:

    private:
};

#endif // BENCHMARK_1999_F4_H
