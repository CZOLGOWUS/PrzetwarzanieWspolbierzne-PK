#include "Matrix.hpp"
#include <string>
#include <random>

using std::cout;
using std::cin;
using std::endl;


#define VEC_SIZE 100000000


Matrix* createRandomVector(size_t size)
{
    Matrix* res = new Matrix(size, 1,0);
    #pragma omp parallel for shared(res)
    for (int i = 0; i < size; i++)
    {
        res->set(i,0, rand() % 10 + 1);
    }

    return res;
}


Matrix* multiVec(const Matrix& m1, const Matrix& m2)
{
    if (m1.rows() != m2.rows())
    {
        std::cout << "vectors cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* multiM = new Matrix(m1.rows(), 1,  0.0);

    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

    return multiM;
}

Matrix* multiVec123(const Matrix& m1, const Matrix& m2)
{
    if (m1.rows() != m2.rows())
    {
        std::cout << "vectors cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* multiM = new Matrix(m1.rows(), 1,  0.0);

    double t1 = 0, t2 = 0;

    t1 = omp_get_wtime();
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for no parallel 1 loop: " << t2-t1 << "s\n";

    t1 = omp_get_wtime();
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for no parallel 2 loop: " << t2-t1 << "s\n";
    
    t1 = omp_get_wtime();
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for no parallel 3 loop: " << t2-t1 << "s\n";

    return multiM;
}


Matrix* multiVecOMP123(const Matrix& m1, const Matrix& m2)
{
    if (m1.rows() != m2.rows())
    {
        std::cout << "vectors cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* multiM = new Matrix(m1.rows(), 1,  0.0);

    double t1 = 0, t2 =0;

    t1 = omp_get_wtime();
    #pragma omp parallel for
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for OMP parallel 1 loop: " << t2-t1 << "s\n";

    t1 = omp_get_wtime();
    #pragma omp parallel for
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for OMP parallel 2 loop: " << t2-t1 << "s\n";

    t1 = omp_get_wtime();
    #pragma omp parallel for
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for OMP parallel 3 loop: " << t2-t1 << "s\n";

    return multiM;
}



Matrix* multiVecSIMD123(const Matrix& m1, const Matrix& m2)
{
    if (m1.rows() != m2.rows())
    {
        std::cout << "vectors cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* multiM = new Matrix(m1.rows(), 1,  0.0);

    double t1 = 0, t2 =0;

    t1 = omp_get_wtime();
    #pragma omp simd
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for SIMD parallel 1 loop: " << t2-t1 << "s\n";

    t1 = omp_get_wtime();
    #pragma omp simd
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for SIMD parallel 2 loop: " << t2-t1 << "s\n";

    t1 = omp_get_wtime();
    #pragma omp simd
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    t2 = omp_get_wtime();
    cout << "for SIMD parallel 3 loop: " << t2-t1 << "s\n";

    return multiM;
}




int main()
{

    srand(time(NULL));

    Matrix* v1 = createRandomVector(VEC_SIZE);
    Matrix* v2 = createRandomVector(VEC_SIZE);

    double t1=0,t2=0;

    Matrix* res;

    res = multiVec123(*v1,*v2);
    delete res;

    res = multiVecOMP123(*v1,*v2);
    delete res;

    res = multiVecSIMD123(*v1,*v2);
    delete res;

    delete v1,v2;
    return 0;
}


