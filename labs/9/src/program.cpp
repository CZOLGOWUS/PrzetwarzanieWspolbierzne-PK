#include <stdlib.h>
#include <stdio.h>
#include "mpi.h" 
#include <iostream>

int main(int argc, char** argv)
{
    int rank, ranksent, size, source, dest, tag, i, len;
    char name[20];
    len = 20;
    MPI_Status status;

    int msg;
    int msg_rcv;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(name, &len);

    if (rank == 0)
    {
        std::cout << "enter a Integer for msg:\n";
        std::cin >> msg;

        dest = 0;
        tag = 0;

        MPI_Send(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        
        MPI_Recv(&msg_rcv, 1, MPI_INT, size-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Proces %d dostał %d od procesu %d\n", rank, msg_rcv ,status.MPI_SOURCE);

    }
    else
    {
        MPI_Recv(&msg_rcv, 1, MPI_INT, (rank - 1) , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        msg = msg_rcv;
        
        printf("Proces %d dostał %d od procesu %d\n", rank, msg_rcv ,status.MPI_SOURCE);
        MPI_Send(&msg, 1, MPI_INT, (rank+1) % size, status.MPI_SOURCE, MPI_COMM_WORLD);

    }

    MPI_Finalize();
    return(0);
}

