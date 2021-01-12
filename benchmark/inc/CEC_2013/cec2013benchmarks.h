#ifndef CEC2013BENCHMARKS_H
#define CEC2013BENCHMARKS_H
#include "../Benchmarks.h"

class CEC2013Benchmarks:public Benchmarks
{
    public:
        CEC2013Benchmarks();
        CEC2013Benchmarks(int,int);
        double compute(double*);
        virtual ~CEC2013Benchmarks();
        void test_func(double*,double*,int,int,int);
        void oszfunc(double*, double*, int);
        void sphere_func(double*, double*, int, double*, double*, int); /* Sphere */
        void ellips_func(double*, double*, int, double*, double*, int); /* Ellipsoidal */
        void bent_cigar_func(double*, double*, int, double*, double*, int); /* Discus */
        void discus_func(double*, double*, int, double*, double*, int);  /* Bent_Cigar */
        void dif_powers_func(double*, double*, int, double*, double*, int);  /* Different Powers */
        void rosenbrock_func(double*, double*, int, double*, double*, int); /* Rosenbrock's */
        void schaffer_F7_func(double*, double*, int, double*, double*, int); /* Schwefel's F7 */
        void ackley_func(double*, double*, int, double*, double*, int); /* Ackley's */
        void rastrigin_func(double*, double*, int, double*, double*, int); /* Rastrigin's  */
        void weierstrass_func(double*, double*, int, double*, double*, int); /* Weierstrass's  */
        void griewank_func(double*, double*, int, double*, double*, int); /* Griewank's  */
        void schwefel_func(double*, double*, int, double*, double*, int); /* Schwefel's */
        void katsuura_func(double*, double*, int, double*, double*, int); /* Katsuura */
        void bi_rastrigin_func(double*, double*, int, double*, double*, int); /* Lunacek Bi_rastrigin */
        void grie_rosen_func(double*, double*, int, double*, double*, int); /* Griewank-Rosenbrock  */
        void escaffer6_func(double*, double*, int, double*, double*, int); /* Expanded Scaffer's F6  */
        void step_rastrigin_func(double*, double*, int, double*, double*, int); /* Noncontinuous Rastrigin's  */
        void cf01(double*, double*, int, double*, double*, int); /* Composition Function 1 */
        void cf02(double*, double*, int, double*, double*, int); /* Composition Function 2 */
        void cf03(double*, double*, int, double*, double*, int); /* Composition Function 3 */
        void cf04(double*, double*, int, double*, double*, int); /* Composition Function 4 */
        void cf05(double*, double*, int, double*, double*, int); /* Composition Function 5 */
        void cf06(double*, double*, int, double*, double*, int); /* Composition Function 6 */
        void cf07(double*, double*, int, double*, double*, int); /* Composition Function 7 */
        void cf08(double*, double*, int, double*, double*, int); /* Composition Function 8 */

        void shiftfunc(double*, double*, int, double*);
        void rotatefunc(double*, double*, int, double*);
        void asyfunc(double*, double* x, int, double);
        //void oszfunc (double *, double *, int);
        void cf_cal(double*, double*, int, double*, double*, double*, double*, int);
    protected:
        int dim = -1, funcID = -1;
    private:
        int ini_flag = 0, n_flag, func_flag;
        double* OShift, * m, * y, * z, * x_bound;
};

#endif // CEC2013BENCHMARKS_H
