
#include "Matrix.hpp"
#include <omp.h>

// De\- Construktors
Matrix::Matrix()
{
    _xSize = 1;
    _ySize = 1;

    _matrix = InstanciateMatrix(1, 1);
    _matrix[0][0] = 1;
}



Matrix::Matrix(int x)
{
    _ySize = x;
    _xSize = x;

    _matrix = InstanciateMatrix(x, x);

    for (int i = 0; i < _xSize; i++)
        for (int j = 0; j < _xSize; j++)
            set(i, j, 0);
}



Matrix::Matrix(int x, int y)
{
    _ySize = y;
    _xSize = x;

    _matrix = InstanciateMatrix(x, y);

    for (int i = 0; i < _xSize; i++)
        for (int j = 0; j < _ySize; j++)
        {
            set(i, j, 0);
        }
}



Matrix::Matrix(int x, int y, double z)
{
    _ySize = y;
    _xSize = x;

    _matrix = InstanciateMatrix(x, y);

    for (int i = 0; i < _xSize; i++)
        for (int j = 0; j < _ySize; j++)
            set(i, j, z);
}



Matrix::Matrix(std::string path)
{
    int x = 0, y = 0;
    std::list<double> listOfMatrixNumbers;

    std::ifstream file;

    std::string line;
    std::string numberString;

    file.open(path, std::iostream::out);
    if (!file.is_open())
    {
        std::cout << "could not open file : constructor aborted\n";
        exit(-1);
    }

    while (std::getline(file, line))
    {
        char* c = &line[0];
        char* tempCharPointer = c;
        //47 = '/' , 124 = '|'
        while (*(tempCharPointer) != '\0')
        {

            switch (*c)
            {
            case 47: // = '/'
            {
                ++c;
                while (*c != '/' && *c != '|')
                {
                    numberString.append(std::string(1, *c));
                    c++;
                }

                if (*c == '/')
                    x = stoi(numberString);
                else
                    y = stoi(numberString);

                numberString = "";

            }
            break;

            case 124: // = '|'
            {
                ++c;
                while (c != nullptr && *c != '|')
                {

                    numberString.append(std::string(1, *c));
                    c++;
                }

                listOfMatrixNumbers.push_back(stod(numberString));
                numberString = "";

            }
            break;

            default:
                break;
            }

            tempCharPointer = c;
            ++tempCharPointer;

        }
    }

    this->_xSize = x;
    this->_ySize = y;

    _matrix = InstanciateMatrix(x, y);

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
        {
            set(i, j, listOfMatrixNumbers.front());
            listOfMatrixNumbers.pop_front();
        }
}



Matrix::~Matrix()
{
    for (int i = 0; i < _xSize; i++)
    {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}



//Matrixis in making
Matrix* Matrix::duplicate() const
{
    return new Matrix();
}
double** Matrix::InstanciateMatrix(int x, int y)
{
    double** matrix = new double* [x];
    for (int i = 0; i < x; i++)
        matrix[i] = new double[y];

    return matrix;
}



//Operations
void Matrix::operator=(const Matrix& m2)
{
    //M3 =    ( M2 + M5)// = m2 ;
    Matrix placeHolderM(m2._ySize, m2._ySize);
    placeHolderM._matrix = InstanciateMatrix(m2._xSize, m2._ySize);

    for (int i = 0; i < m2._xSize; i++)
        for (int j = 0; j < m2._ySize; j++)
        {
            placeHolderM._matrix[i][j] = m2._matrix[i][j];
        }

    this->_ySize = placeHolderM._ySize;
    this->_xSize = placeHolderM._xSize;
    this->_matrix = placeHolderM._matrix;

    placeHolderM._matrix = nullptr;

}



Matrix* Matrix::add(const Matrix& m2) const
{
    if (!(this->_xSize == m2._xSize && this->_ySize == m2._ySize))
    {
        std::cout << "matrixies cannot be added : diffrent sizes\n";
        exit(-1);
    }

    Matrix* AddedM = new Matrix(this->_xSize, this->_ySize);

    for (int i = 0; i < this->_xSize; i++)
        for (int j = 0; j < this->_ySize; j++)
        {
            AddedM->set(i, j, this->get(i, j) + m2.get(i, j));
        }

    return AddedM;
}



Matrix* Matrix::operator+(const Matrix& M2) const
{
    if (_xSize != M2._xSize || _ySize != M2._ySize)
    {
        std::cout << "Dimensions don't match!" << std::endl;
        exit(-1);
    }

    Matrix* new_mat = new Matrix(_xSize, _ySize);
    for (int i = 0; i < _xSize; i++)
    {
        for (int j = 0; j < _ySize; j++)
        {
            new_mat->_matrix[i][j] = _matrix[i][j] + M2._matrix[i][j];
        }
    }
    return new_mat;
}



Matrix* Matrix::subb(const Matrix& m2) const
{
    if (!(this->_xSize == m2._xSize && this->_ySize == m2._ySize))
    {
        std::cout << "matrixies cannot be added : diffrent sizes\n";
        exit(-1);
    }

    Matrix* SubbM = new Matrix(this->_xSize, this->_ySize);

    for (int i = 0; i < this->_xSize; i++)
        for (int j = 0; j < this->_ySize; j++)
        {
            SubbM->set(i, j, this->get(i, j) - m2.get(i, j) + i);
        }

    return SubbM;
}



Matrix* Matrix::operator-(const Matrix& m2) const
{
    if (!(this->_xSize == m2._xSize && this->_ySize == m2._ySize))
    {
        std::cout << "matrixies cannot be added : diffrent sizes\n";
        exit(-1);
    }

    Matrix* SubbM = new Matrix(this->_xSize, this->_ySize);

    for (int i = 0; i < this->_xSize; i++)
        for (int j = 0; j < this->_ySize; j++)
        {
            SubbM->set(i, j, this->get(i, j) - m2.get(i, j) + i);
        }

    return SubbM;
}



Matrix* Matrix::multi(const  Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    for (int i = 0; i < this->_xSize; i++)
    {
        for (int j = 0; j < m2._ySize; j++)
        {
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}


Matrix* Matrix::multiParallelFirstLoop(const  Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    #pragma omp parallel for schedule(static,5) num_threads(7) 
    for (int i = 0; i < this->_xSize; i++)
    {
        for (int j = 0; j < m2._ySize; j++)
        {
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}

Matrix* Matrix::multiParallelSecondLoop(const Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    for (int i = 0; i < this->_xSize; i++)
    {
        #pragma omp parallel for num_threads(7) schedule(static,5)
        for (int j = 0; j < m2._ySize; j++)
        {
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}


Matrix* Matrix::multiParallelThirdLoop(const  Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    for (int i = 0; i < this->_xSize; i++)
    {
        for (int j = 0; j < m2._ySize; j++)
        {
            #pragma omp parallel for num_threads(7) schedule(static,5)
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}



Matrix* Matrix::multiParallelFirstSecondLoop(const  Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    #pragma omp parallel for num_threads(7) schedule(static,5)
    for (int i = 0; i < this->_xSize; i++)
    {
        #pragma omp parallel for num_threads(7) schedule(static,5)
        for (int j = 0; j < m2._ySize; j++)
        {
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}



Matrix* Matrix::multiParallelFirstSecondThirdLoop(const  Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    #pragma omp parallel for num_threads(7) schedule(static,5)
    for (int i = 0; i < this->_xSize; i++)
    {
        #pragma omp parallel for num_threads(7) schedule(static,5)
        for (int j = 0; j < m2._ySize; j++)
        {
            #pragma omp parallel for num_threads(7) schedule(static,5)
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}




Matrix* Matrix::multiParallelSecondThirdLoop(const  Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    for (int i = 0; i < this->_xSize; i++)
    {
        #pragma omp parallel for num_threads(7) schedule(static,5)
        for (int j = 0; j < m2._ySize; j++)
        {
            #pragma omp parallel for num_threads(7) schedule(static,5)
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}




Matrix* Matrix::multiParallelFirstThirdLoop(const  Matrix& m2) const
{
    if (m2._xSize != this->_ySize)
    {
        std::cout << "matrixies cannot be multiplied : diffrent sizes\n";
        exit(-1);
    }

    Matrix* MultiM = new Matrix(this->_xSize, m2._ySize, (double)0);

    #pragma omp parallel for num_threads(7) schedule(static,5)
    for (int i = 0; i < this->_xSize; i++)
    {
        for (int j = 0; j < m2._ySize; j++)
        {
            #pragma omp parallel for num_threads(7) schedule(static,5)
            for (int k = 0; k < this->_ySize; k++)
                MultiM->_matrix[i][j] += this->get(i, k) * m2.get(k, j);
        }
    }
    return MultiM;
}



//defult methods
void Matrix::set(int x = 0, int y = 0, double val = 0)
{
    if (x < _xSize && y < _ySize)
        _matrix[x][y] = val;
    else
    {
        std::cout << "set() error : out of bounds exeption\n";
        exit(-1);
    }
}



double Matrix::get(int x, int y) const
{
    if (x < _xSize && y < _ySize && x >= 0 && y >= 0)
        return _matrix[x][y];
    else
    {
        std::cout << "get() error : out of bounds exeption\n";
        exit(-1);
    }
}



void Matrix::PrintMatrix()const
{
    int largerstNumber = 0;
    int k;
    for (int i = 0; i < _xSize; i++)
        for (int j = 0; j < _ySize; j++)
        {
            k = std::to_string(_matrix[i][j]).length();
            if (k > largerstNumber)
            {
                largerstNumber = k;
            }
        }

    for (int i = 0; i < _xSize; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < _ySize; j++)
        {
            std::cout << std::setw(largerstNumber - 5) << _matrix[i][j] << " ";
        }
        std::cout << " |\n";
    }
    std::cout << "\n";
}



int Matrix::cols() const
{
    return this->_ySize;
}



int Matrix::rows() const
{
    return this->_xSize;
}



void Matrix::store(std::string filename, std::string path) const
{
    std::ofstream file;

    file.open(path + "//" + filename);
    if (file.is_open())
    {
        std::string placeHolderString;
        file << '/' << _xSize << '/' << _ySize << '|';
        for (int x = 0; x < _xSize; x++)
            for (int y = 0; y < _ySize; y++)
            {
                placeHolderString.append(std::to_string(_matrix[x][y]) + '|');
            }
        file << placeHolderString;
        file.close();
        return;
    }

    std::cout << "file : " << filename << " could not be opened\n";
    exit(-1);

}