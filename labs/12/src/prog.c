#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

struct range_st
{
    int begin;
    int end;
};

int main(int argc, char **argv)
{
    int i;
    int rank, size, rangeLength;
    MPI_Aint extent;
    MPI_Datatype range_type;
    struct range_st range;
    int array_length;
    int remainingRange;

    if(argc != 2)
    {
        printf("bad invocation: <PROGRAM> <rangeAY_LENGTH>");
        exit(EXIT_FAILURE);
    }

    array_length = atoi(argv[1]);

    range.begin = 0;
    range.end = 0;

    MPI_Aint offsets[2];

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    offsets[0] = 0;
    MPI_Type_extent(MPI_INT, &extent);
    offsets[1] = extent;
    MPI_Type_extent(MPI_INT, &extent);
    offsets[2] = offsets[1] + extent;

    rangeLength = array_length / size;
    remainingRange = array_length % size;

    int blockcounts[] = {1, 1};
    MPI_Datatype oldtypes[] = {MPI_INT, MPI_INT };

    MPI_Type_struct(2, blockcounts, offsets, oldtypes, &range_type);
    MPI_Type_commit(&range_type);

    
    double process_res = 0;
    double result = 0;
    if (rank == 0)
    {
        
        for (size_t i = 1; i < size; i++)
        {
            range.begin = rangeLength*(i-1);
            range.end = rangeLength*i;


            MPI_Send(&range, 1, range_type, i, 0, MPI_COMM_WORLD);
        }

        

        for (size_t i = 1; i < size; i++)
        {
            MPI_Recv(&process_res, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            result += process_res;
        }

        // adding the rest of the range (remaining part)
        for (size_t i = array_length - remainingRange; i < array_length; i++)
        {
            short znak;
            for(size_t i = range.begin; i <= range.end; i++)
            {
                znak = (i % 2) == 0 ? 1 : -1;
                result += znak*(1.0 /( 2.0 * i + 1.0 ));
            }
        }
        

        result = 4 * result;

        printf("result = %f\n",result);
    }
    else
    {
        MPI_Recv(&range, 1, range_type, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        short znak;
        for(size_t i = range.begin; i <= range.end; i++)
        {
            znak = (i % 2) == 0 ? 1 : -1;
            process_res += znak*(1.0 /( 2.0 * i + 1.0 ));
        }

        MPI_Send(&process_res, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return (0);
}
