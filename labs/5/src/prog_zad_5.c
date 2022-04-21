#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    int number_of_iterations = 0;
    if (argc != 2)
    {
        printf("Bad Invocation: <PROGRAM_NAME> <NUMBER>\n");
    }

    if (argv[1] == "0")
    {
        printf("result: %d\n", 0);
        exit(EXIT_SUCCESS);
    }

    if ((number_of_iterations = atoi(argv[1])) == 0)
    {
        perror("atoi()");
        exit(EXIT_FAILURE);
    }

    printf("for all threads baseline is -> shared num_threads(5) schedule(static,10)\n\n");


    {
        printf("=====================================================\natomic\n");
        long long sum = 0;
        double start_time, end_time;

        start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(5) schedule(static,10) 
        for (size_t i = 0; i < number_of_iterations; i++)
        {
        #pragma omp atomic
            sum += i * i;
        }

        end_time = omp_get_wtime();
        printf("result: %lld\n", sum);
        printf("time of excecution: %f \n=====================================================\n\n", end_time - start_time);

    }

    {
        printf("=====================================================\ncritical\n");
        long long sum = 0;
        double start_time, end_time;

        start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(5) schedule(static,10) 
        for (size_t i = 0; i < number_of_iterations; i++)
        {
        #pragma omp critical
            sum += i * i;
        }

        end_time = omp_get_wtime();
        printf("result: %lld\n", sum);
        printf("time of excecution: %f \n=====================================================\n\n", end_time - start_time);

    }

    {
        printf("=====================================================\nlock\n");
        long long sum = 0;
        double start_time, end_time;


        start_time = omp_get_wtime();
        omp_lock_t add_lock;
        omp_init_lock(&add_lock);
    #pragma omp parallel for num_threads(5) schedule(static,10) 
        for (size_t i = 0; i < number_of_iterations; i++)
        {
            omp_set_lock(&add_lock);
            sum += i * i;
            omp_unset_lock(&add_lock);
        }
        omp_destroy_lock(&add_lock);
        end_time = omp_get_wtime();


        printf("result: %lld\n", sum);
        printf("time of excecution: %f \n=====================================================\n\n", end_time - start_time);

    }


    {
        printf("=====================================================\nreduction\n");
        long long sum = 0;
        double start_time, end_time;


        start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(5) schedule(static,10) reduction(+:sum)
        for (size_t i = 0; i < number_of_iterations; i++)
        {
            sum += i * i;
        }

        end_time = omp_get_wtime();


        printf("result: %lld\n", sum);
        printf("time of excecution: %f \n=====================================================\n\n", end_time - start_time);

    }


    return 0;
}