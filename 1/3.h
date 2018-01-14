#pragma once
template <class T>
void p88_squareMatrixMultiply(T **a, T **b, T **c, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; i < n; j++)
            sum += a[i][k] * b[k][j];
        c[i][j] = sum;
    }  
}