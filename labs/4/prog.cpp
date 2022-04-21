#include <iostream>
#include <algorithm>
#include <vector>


#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_ENTRY_ARRAY 100000
#define MAX_PRIME_ARRAY 10000
#define MAX_THREADS 1000

struct PrimeRefArr
{
	std::vector<int> m_naturals;
	pthread_mutex_t m_change_mutex;
	int m_last_number_checked;

	PrimeRefArr()
	{
		for (int i = 0; i < MAX_ENTRY_ARRAY; i++)
		{
			m_naturals.push_back(i);
		}
		
		m_last_number_checked = 2;
		m_change_mutex = PTHREAD_MUTEX_INITIALIZER;
	}
	
	~PrimeRefArr() = default;

}typedef primes_arr;


bool isPrime(int n)
{
    // Corner case
    if (n <= 1)
        return false;
  
    // Check from 2 to n-1
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
  
    return true;
}


void* erase_next_multiple(void* arg)
{
	primes_arr* ref = (primes_arr*)arg;

	if(pthread_mutex_lock(&(ref->m_change_mutex)) != 0)
	{
		std::cout << "mutex locking error\n";
		return nullptr;
	}

	int current_number = ref->m_last_number_checked;
	ref->m_last_number_checked++;

	if(pthread_mutex_unlock(&(ref->m_change_mutex)) != 0)
	{
		std::cout << "mutex unlocking error\n";
		return nullptr;
	}

	if( ref->m_naturals.at(current_number) == -1)
		return nullptr;
	
	for (int i = 2; current_number * i < MAX_ENTRY_ARRAY; i++)
	{
		ref->m_naturals.at(current_number * i) = -1;
	}

	return nullptr;

}



int main(int arg, char* argv[])
{
	using std::cout;

	pthread_t threads[MAX_THREADS];
	int actual_number_of_threads = 0;

	PrimeRefArr refArr{};

	for (int i = 0; i < MAX_THREADS; i++)
	{
		if(i > refArr.m_naturals.size())
		{
			break;
		}
		actual_number_of_threads++;
		pthread_create(&threads[i],NULL,erase_next_multiple,(void*)&refArr);
	}
	

	for (int i = 0; i < actual_number_of_threads; i++)
	{
		pthread_join(threads[i],NULL);
	}

	refArr.m_naturals.erase(std::remove(refArr.m_naturals.begin(),refArr.m_naturals.end(),-1),refArr.m_naturals.end());

	for (int i = 0; i < refArr.m_naturals.size(); i++)
	{
		cout << refArr.m_naturals[i] << "->" << ((isPrime(refArr.m_naturals[i]) == 1) ? "true": "false")  << "  \n";
	}

	return 0;
	

}
