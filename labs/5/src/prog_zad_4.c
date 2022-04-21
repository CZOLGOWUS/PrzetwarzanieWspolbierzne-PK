#include <stdio.h>
#include <omp.h>

#define MAX_NUM_ITERRATIONS 10000000

int main()
{

    {
        int a = 0;
        double start_time,end_time;
        printf("======= static with partition size of 3 ========\n");
        start_time = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(static, 3) 
        for (int i = 0; i < MAX_NUM_ITERRATIONS; i++)
        {
            a++;
        }
        end_time = omp_get_wtime();

        printf("time of execution: %f\n==============================================\n\n",end_time-start_time);
    }


        {
        int a = 0;
        double start_time,end_time;
        printf("======= static with partition default ========\n");
        start_time = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(static) 
        for (int i = 0; i < MAX_NUM_ITERRATIONS; i++)
        {
            a++;
        }
        end_time = omp_get_wtime();

        printf("time of execution: %f\n==============================================\n\n",end_time-start_time);
    }



        {
        int a = 0;
        double start_time,end_time;
        printf("======= dynamic with partition size of 3 ========\n");
        start_time = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(dynamic, 3) 
        for (int i = 0; i < MAX_NUM_ITERRATIONS; i++)
        {
            a++;
        }
        end_time = omp_get_wtime();

        printf("time of execution: %f\n==============================================\n\n",end_time-start_time);
    }



        {
        int a = 0;
        double start_time,end_time;
        printf("======= dynamic with partition default ========\n");
        start_time = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(dynamic) 
        for (int i = 0; i < MAX_NUM_ITERRATIONS; i++)
        {
            a++;
        }
        end_time = omp_get_wtime();

        printf("time of execution: %f\n==============================================\n\n",end_time-start_time);
    }

}