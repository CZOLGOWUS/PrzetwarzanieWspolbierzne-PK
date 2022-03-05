#include<stdio.h>

#include "pomiar_czasu.h"

void petlaPrint(int liczbaIteracji)
{
    inicjuj_czas();
    for (int i = 0; i < liczbaIteracji; i++)
    {
        printf("c ");
    }
    printf("\n");
    drukuj_czas();
}

void petlaArytmetyczna(int liczbaOperacji)
{
    inicjuj_czas();
    int x = 0;
    float y = 2;
    for (int i = 0; i < liczbaOperacji; i++)
    {
        x = 5+8+5*8/65*4*7+84746+4848*64*8+486+432;
        x = 5+8+5*8/65*4*7+84746+4848*64*8+486+432;
        x = 5+8+5*8/65*4*7+84746+4848*64*8+486+432;
        x = 5+8+5*8/65*4*7+84746+4848*64*8+486+432;
        x = 5+8+5*8/65*4*7+84746+4848*64*8+486+432;
        x = 5+8+5*8/65*4*7+84746+4848*64*8+486+432;
        x = 5+8+5*8/65*4*7+84746+4848*64*8+486+432;
        y = x*x/0.5f;
    }
    x++;
    y++;
    x++;
    drukuj_czas();
}


int main()
{
    printf("petla print:");
    petlaPrint(10000000);
    printf("\n\npetla arytmetyczna:\n");
    petlaArytmetyczna(100000000);
}