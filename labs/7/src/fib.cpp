#include <iostream>
#include <string>
#include <omp.h>

using std::cout;
using std::cin;
using std::endl;

// unsigned long fibRec(unsigned short n, unsigned long first = 0, unsigned long second = 1)
// {
//     if (n == 0)
//         return 0;
//
//     if (n == 1 || n == 2)
//         return 1;
//
//     return fibRec(n-1,second,first+second) + second;
//
// }

unsigned long fibRec(unsigned long n)
{
    if (n == 1 || n == 0)
        return(n);

    unsigned long temp = 0;
    temp = (fibRec(n - 1) + fibRec(n - 2));
    return temp;
}





unsigned long fibRecTASK1(unsigned long n)
{
    if (n == 1 || n == 0)
        return(n);

    unsigned long temp = 0, a = 0, b = 0;

#pragma omp task shared(a)
    a = fibRecTASK1(n - 1);

#pragma omp task shared(b)
    b = fibRecTASK1(n - 2);

#pragma omp taskwait
    temp = a + b;
    return temp;
}




unsigned long fibRecTASK2(unsigned long n)
{
    if (n == 1 || n == 0)
        return(n);

    unsigned long temp = 0, a = 0, b = 0;
    if (n > 20)
    {
        #pragma omp task shared(a)
        a = fibRecTASK2(n - 1);

        #pragma omp task shared(b)
        b = fibRecTASK2(n - 2);

        #pragma omp taskwait
        temp = a + b;
        return temp;
    }
    else
    {
        a = fibRecTASK2(n - 1);
        b = fibRecTASK2(n - 2);
        temp = a + b;
        return temp;
    }

}


int main(int argc, char** argv)
{
    int arg = std::stoi(argv[1]);

    double t1, t2;
    unsigned long res = 0;

    t1 = omp_get_wtime();
    res = fibRec(arg);
    t2 = omp_get_wtime();
    cout << "fib no tasks: " << res << " ,with time: " << t2 - t1 << "s\n";



    res = 0;
    t1 = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            res = fibRecTASK1(arg);
        }
    }
    t2 = omp_get_wtime();

    cout << "fib tasks: " << res << " ,with time: " << (t2 - t1) << "s\n";


    res = 0;
    t1 = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            res = fibRecTASK2(arg);
        }
    }
    t2 = omp_get_wtime();

    cout << "fib tasks with if: " << res << " ,with time: " << (t2 - t1) << "s\n";


    return 0;
}


