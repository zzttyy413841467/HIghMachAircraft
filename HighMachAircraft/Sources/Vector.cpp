#include "Vector.h"

Matrix<double> zeros(int m, int n)
{
    Matrix<double> temp(m, n, 0);
    return temp;
}

Matrix<double> ones(int m, int n)
{
    Matrix<double> temp(m, n, 1);
    return temp;
}

Matrix<double> eye(int m, int n)
{
    Matrix<double> temp(m, n, 0);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                temp[i][j] = 1.0;
        }
    }
    return temp;
}