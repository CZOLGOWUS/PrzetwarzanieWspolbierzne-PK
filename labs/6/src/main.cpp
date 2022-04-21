#include <Matrix.hpp>
#include <string>


#define PATH "result.txt"
#define STARTING_ROWS 100
#define STARTING_COLLS 200
#define MAX_ROWS_AND_COLLS 1000
#define INCREMENT_ROWS_COLLS 100;

void writeResultToFile(uint16_t number_of_elem, std::string strategy, double time)
{
    #pragma omp critical
    {
        std::fstream file;
        file.open(PATH, std::ios::app);

        if (!file)
        {
            std::cout << "file : " << PATH << " could not be opened\n";
            exit(-1);
        }

        file << number_of_elem << " "<< strategy <<" " << time << std::endl;
        file.close();
    }

}

int main()
{
    std::fstream file;
    Matrix* p;


    file.open(PATH, std::ios::out);

    if (!file)
    {
        std::cout << "file : " << PATH << " could not be opened\n";
        exit(-1);
    }
    file << "Matrix_size(M*N) strategy time\n";
    file.close();




    printf("0 = no loop was parallel\n1 = first loop only\n2 = second loop only\n23 = second and third loop \netc.\n\n");
    printf("=================== 0 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multi(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"0",end_time-start_time);
        
    }


    printf("=================== 1 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multiParallelFirstLoop(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"1",end_time-start_time);
        
    }


    printf("=================== 2 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multiParallelSecondLoop(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"2",end_time-start_time);
        
    }



    printf("=================== 3 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multiParallelThirdLoop(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"3",end_time-start_time);
        
    }



    printf("=================== 12 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multiParallelFirstSecondLoop(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"12",end_time-start_time);
        
    }



    printf("=================== 123 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multiParallelFirstSecondThirdLoop(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"123",end_time-start_time);
        
    }


    printf("=================== 23 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multiParallelSecondThirdLoop(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"23",end_time-start_time);
        
    }



    printf("=================== 13 loop ====================\n");
    for (uint16_t j = STARTING_ROWS, i = STARTING_COLLS; i < MAX_ROWS_AND_COLLS; i+=100, j += 100)
    {
        Matrix A(i,j,2);
        Matrix B(j,i,10);
        double start_time, end_time;

        start_time = omp_get_wtime();

        p = A.multiParallelFirstThirdLoop(B);

        end_time = omp_get_wtime();

        //bardzo duzy buffor na stdin - debug
        //p->PrintMatrix();

        printf("time of excecution: %f \n", end_time - start_time);
        writeResultToFile(i*j,"13",end_time-start_time);
        
    }




    delete p;

    return 0;
}


