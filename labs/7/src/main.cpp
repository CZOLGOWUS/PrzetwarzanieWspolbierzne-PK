#include "Matrix.hpp"
#include <string>
#include <random>

using std::cout;
using std::cin;
using std::endl;

#define VEC_SIZE 1000000000


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

    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }
    
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

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

    #pragma omp parallel for
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

    #pragma omp parallel for
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

    #pragma omp parallel for
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

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

    #pragma omp simd
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

    #pragma omp simd
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

    #pragma omp simd
    for (int j = 0; j < multiM->rows(); j++)
    {
        multiM->set(j,0, m1.get(j,0) * m2.get(j,0) ); 
    }

    return multiM;
}




int main()
{

    srand(time(NULL));

    Matrix* v1 = createRandomVector(VEC_SIZE);
    Matrix* v2 = createRandomVector(VEC_SIZE);

    v1->PrintMatrix();
    //multiVec(*v1,*v2)->PrintMatrix();




    delete v1,v2;
    return 0;
}


