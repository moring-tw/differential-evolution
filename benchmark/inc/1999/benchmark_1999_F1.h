#ifndef BENCHMARK_1999_F1_H
#define BENCHMARK_1999_F1_H

#include "../Benchmarks.h"

class benchmark_1999_F1:public Benchmarks
{
    public:
        benchmark_1999_F1();
        double compute(double*);
        virtual ~benchmark_1999_F1();

    protected:

    private:
};

#endif // BENCHMARK_1999_F1_H
