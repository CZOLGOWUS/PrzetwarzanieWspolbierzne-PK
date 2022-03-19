#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct pub_stock
{
    int number_of_mugs;
    int clients_served;
    int max_drinking_time;
    pthread_mutex_t* mugs_mutex_array;

}typedef PUB;


void* client(void* arg)
{

    PUB* pub = (PUB*)arg;
    ++pub->clients_served;
    int id_client = pub->clients_served;
    int id_mug;
    int liter_count = 0;

    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; ; i++)
    {
        if(i >= pub->number_of_mugs)
        {
            i = 0;
        }

        if(pthread_mutex_trylock(&(pub->mugs_mutex_array[i])) == 0)
        {
            id_mug = i;
            printf("Klient nr %d zamawia piwo w kulfu nr %d\n",id_client,id_mug);
            ++liter_count;

            unsigned int drinking_time = abs( (rand() % (pub->max_drinking_time - 5) ) + 5);
            usleep(drinking_time * 1000);
            
            pthread_mutex_unlock(&(pub->mugs_mutex_array[i]));
            printf("Klient nr %d oddaje kulfel nr %d po czasie %dms\n",id_client,id_mug,drinking_time);

            id_mug = -1;
        }

        if(liter_count >= 2)
        {
            return NULL;
        }
    }

    return NULL;

}





int main(int arg, char* argv[])
{
    if(arg != 4)
	{
		printf("wrong number of arguments\n./pub <NUMBER_OF_CLIENTS> <NUMBER_OF_MUGS> <MAX_DRINGING_TIME_IN_MS>");
		exit(EXIT_FAILURE);
	}

	int number_of_clients = atoi(argv[1]);
	int number_of_mugs = atoi(argv[2]);
	int max_drinking_time = atoi(argv[3]);


    pthread_t mugs[number_of_mugs];
	pthread_t clients[number_of_clients];

    PUB pub_stock = 
    {
        .number_of_mugs = number_of_mugs,
        .clients_served = 0,
        .max_drinking_time = max_drinking_time,
        .mugs_mutex_array = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*number_of_mugs)
    };



    //initialize mutexes on mugs
    for(int i = 0; i < number_of_mugs ; i++)
    {
        pub_stock.mugs_mutex_array[i] = PTHREAD_MUTEX_INITIALIZER;
    }

	for(int i = 0; i < number_of_clients ; i++)
	{
		pthread_create(&clients[i],NULL,client,(void*)&pub_stock);
        //printf("+++++++ %d\n",i);
	}

	for(int i = 0; i < number_of_clients ; i++)
	{
        pthread_join(clients[i], NULL);   
        //printf("------- %d\n",i);
    }




    free(pub_stock.mugs_mutex_array);


}
