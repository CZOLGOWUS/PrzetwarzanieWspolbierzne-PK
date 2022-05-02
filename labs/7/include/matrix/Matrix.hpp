#pragma once

#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <fstream>
#include <list>
#include <omp.h>


class Matrix
{
 /*
wyglad tablic:
   [x][y] 
           y[0] y[1]
             |   |
    x[0] - |0,0|0,1|
    x[1] - |1,0|1,1|
    x[2] - |2,0|2,1|
*/

private:
    double** _matrix;
    int _xSize,_ySize;

    double** InstanciateMatrix(int, int); 

public:
    Matrix();
    Matrix(int x, int y);
    Matrix(int x, int y, double z);
    Matrix(int);
    Matrix(std::string path);
    ~Matrix();

    void store(std::string filename, std::string path) const;

    void operator=(const Matrix&);
    Matrix* operator+(const Matrix& m2) const;
    Matrix* operator-(const Matrix& m2) const;

    Matrix* duplicate() const;
    void set(int y , int x , double val);
    double get(int x, int y) const;
    void PrintMatrix()const;
    Matrix* multi(const Matrix&) const;
    Matrix* add(const Matrix&) const;
    Matrix* subb(const Matrix&) const;
    int cols() const;
    int rows() const;

};