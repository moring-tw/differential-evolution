#ifndef BENCHMARK_1999_F8_H
#define BENCHMARK_1999_F8_H

#include "../Benchmarks.h"
class benchmark_1999_F8:public Benchmarks
{
    public:
        benchmark_1999_F8();
        double compute(double*);
        virtual ~benchmark_1999_F8();

    protected:

    private:
};

#endif // BENCHMARK_1999_F8_H
