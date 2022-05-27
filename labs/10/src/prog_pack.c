#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define MAX_BUFF_SIZE 10000000

struct player_state
{
    char name[20];
    float exp;
    int max_health;
    int might;
    int magic;
} typedef player;

int main(int argc, char **argv)
{
    player p1, p2;

    strcpy(p1.name, "Astrix");
    p1.exp = 685.5f;
    p1.max_health = 100;
    p1.might = 32;
    p1.magic = 7;

    int rank, size, tag, nextrank, prevrank;
    double start, stop;

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

    void *buff, *recv_buff;
    int rozmiar_temp, rozmiar_pakietu;
    MPI_Pack_size(20, MPI_CHAR, MPI_COMM_WORLD, &rozmiar_temp);
    rozmiar_pakietu = rozmiar_temp;
    MPI_Pack_size(1, MPI_FLOAT, MPI_COMM_WORLD, &rozmiar_temp);
    rozmiar_pakietu += rozmiar_temp;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozmiar_temp);
    rozmiar_pakietu += rozmiar_temp;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozmiar_temp);
    rozmiar_pakietu += rozmiar_temp;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozmiar_temp);
    rozmiar_pakietu += rozmiar_temp;

    buff = (void *)malloc(rozmiar_pakietu);
    recv_buff = (void *)malloc(rozmiar_pakietu);
    int pozycja = 0; // ??

    MPI_Pack(&p1.name, 20, MPI_CHAR, buff, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
    MPI_Pack(&p1.exp, 1, MPI_FLOAT, buff, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
    MPI_Pack(&p1.max_health, 1, MPI_INT, buff, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
    MPI_Pack(&p1.might, 1, MPI_INT, buff, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
    MPI_Pack(&p1.magic, 1, MPI_INT, buff, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);

    if (rank == 0)
    {
        player p_temp;
        start = MPI_Wtime();

        MPI_Send(buff, pozycja, MPI_PACKED, nextrank, 0, MPI_COMM_WORLD);
        MPI_Recv(recv_buff, rozmiar_pakietu, MPI_PACKED, prevrank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        stop = MPI_Wtime();

        pozycja = 0;
        MPI_Unpack(recv_buff, rozmiar_pakietu, &pozycja, &p2.name, 20, MPI_CHAR, MPI_COMM_WORLD);
        MPI_Unpack(recv_buff, rozmiar_pakietu, &pozycja, &p2.exp, 1, MPI_FLOAT, MPI_COMM_WORLD);
        MPI_Unpack(recv_buff, rozmiar_pakietu, &pozycja, &p2.max_health, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(recv_buff, rozmiar_pakietu, &pozycja, &p2.might, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(recv_buff, rozmiar_pakietu, &pozycja, &p2.magic, 1, MPI_INT, MPI_COMM_WORLD);

        printf("rank = %d, \nplayer: \n\tname: %s \n\texp: %f\n\tmax health: %d\n\tmight: %d\n\tmagic: %d\n",rank,p2.name,p2.exp,p2.max_health,p2.might,p2.magic);
        printf("time = %f\n", stop - start);

        FILE *wfp = fopen("./pack_case_data.csv", "a+");
        fprintf(wfp, "%d,%lf\n", size, stop - start);
    }
    else
    {
        MPI_Recv(&recv_buff, rozmiar_pakietu, MPI_PACKED, prevrank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Send(&recv_buff, rozmiar_pakietu, MPI_PACKED, nextrank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}