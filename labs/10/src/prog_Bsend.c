#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

/*
usage:
https://www.rookiehpc.com/mpi/docs/mpi_bsend.php
*/

struct player_state
{
    char name[20];
    float exp;
    int max_health;
    int might;
    int magic;
}typedef player;


int main(int argc, char ** argv)
{
    player p1, p2;

    strcpy(p1.name, "Astrix");
    p1.exp = 685.5f;
    p1.max_health = 100;
    p1.might = 32;
    p1.magic = 7;



    int rank, size, tag, nextrank, prevrank;
    double start,stop;

    MPI_Comm inner_comm;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == size - 1)
    {
        prevrank = rank - 1;
        nextrank = 0;
    }
    else if (rank == 0)
    {
        prevrank = size - 1;
        nextrank = rank + 1;
    }
    else
    {
        prevrank = rank - 1;
        nextrank = rank + 1;
    }


    MPI_Aint offset[5];
    MPI_Aint extent;
    MPI_Datatype player_type;
    MPI_Type_extent(MPI_CHAR,&extent);
    offset[0] = 0;
    offset[1] = extent*20;
    MPI_Type_extent(MPI_FLOAT,&extent);
    offset[2] = extent + offset[1];
    MPI_Type_extent(MPI_INT,&extent);
    offset[3] = extent + offset[2];
    MPI_Type_extent(MPI_INT,&extent);
    offset[4] = extent + offset[3];



    int block_counts[] = {20,1,1,1,1};

    MPI_Datatype old_types[] = {MPI_CHAR,MPI_FLOAT,MPI_INT,MPI_INT,MPI_INT};

    MPI_Type_struct(5,block_counts,offset,old_types,&player_type);
    MPI_Type_commit(&player_type);

    int buffer_size = (MPI_BSEND_OVERHEAD + sizeof(player));
    player* buff = malloc(buffer_size);
    MPI_Buffer_attach(buff,buffer_size);

    if(rank == 0)
    {
        
        start = MPI_Wtime();

        MPI_Bsend(&p1, 1, player_type, nextrank, 0, MPI_COMM_WORLD);
        MPI_Recv(&p2, 1, player_type, prevrank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        stop = MPI_Wtime();

        printf("rank = %d, \nplayer: \n\tname: %s \n\texp: %f\n\tmax health: %d\n\tmight: %d\n\tmagic: %d\n",rank,p2.name,p2.exp,p2.max_health,p2.might,p2.magic);
        printf("time = %f\n", stop - start);

        FILE *wfp = fopen("./basic_buffored_data.csv", "a+");
        fprintf(wfp, "%d,%lf\n", size, stop - start);
    }
    else
    {
        MPI_Recv(&p2, 1, player_type, prevrank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Bsend(&p2, 1, player_type, nextrank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;

}