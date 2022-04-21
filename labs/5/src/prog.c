#include <stdio.h>
#include <omp.h>

int main()
{
    {
        printf("shared (no options) ++++++++++++++++++++++++++++++++++++++++++++++++++\n");

        int a = 7;
        double start_time, end_time;

        start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(7)
        for (int i = 0;i < 10;i++)
        {
            printf("Thread %d a=%d\n", omp_get_thread_num(), a);
            a++;
        }
        end_time = omp_get_wtime();
        printf("basic parallel time of execution: %f\n",end_time-start_time);
        printf("================================================== end \'a\' value: %d\n\n",a);
    }

    {
        printf("private ++++++++++++++++++++++++++++++++++++++++++++++++++\n");

        int a = 7;
        double start_time, end_time;

        start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(7) private(a)
        for (int i = 0;i < 10;i++)
        {
            printf("Thread %d a=%d\n", omp_get_thread_num(), a);
            a++;

        }
        end_time = omp_get_wtime();
        printf("basic parallel time of execution: %f\n",end_time-start_time);
        printf("================================================== end \'a\' value: %d\n\n",a );
    }


    {
        printf("firstprivate ++++++++++++++++++++++++++++++++++++++++++++++++++\n");

        int a = 7;
        double start_time, end_time;

        start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(7) firstprivate(a)
        for (int i = 0;i < 10;i++)
        {
            printf("Thread %d a=%d\n", omp_get_thread_num(), a);
            a++;

        }
        end_time = omp_get_wtime();
        printf("basic parallel time of execution: %f\n",end_time-start_time);
        printf("================================================== end \'a\' value: %d\n\n",a );
    }


    {
        printf("lastprivate ++++++++++++++++++++++++++++++++++++++++++++++++++\n");

        int a = 7;
        double start_time, end_time;

        start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(7) lastprivate(a)
        for (int i = 0;i < 10;i++)
        {
            printf("Thread %d a=%d\n", omp_get_thread_num(), a);
            a++;

        }
        end_time = omp_get_wtime();
        printf("basic parallel time of execution: %f\n",end_time-start_time);
        printf("================================================== end \'a\' value: %d\n\n",a );
    }


    return 0;
}
