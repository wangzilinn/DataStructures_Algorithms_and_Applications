#pragma once
template <class T>
class matrix
{
private:
    int rows;//行数
    int cols;//列数
    T * elements;
public:
    matrix(int theRows = 0, int theCols = 0);
    matrix(const matrix<T>&);
    ~matrix() { delete[] elements; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    T& operator()(int i, int j) const;
    matrix<T>& operator=(const matrix<T>&);
    matrix<T> operator+(const matrix<T>&);
    matrix<T> operator+() const;
    matrix<T> operator-(const matrix<T>&);
    matrix<T> operator-() const;
    matrix<T> operator*(const matrix<T>&);
    matrix<T>& operator+=(const matrix<T>&);
    friend ostream & operator<<(ostream & out, const matrix<T> &);
};
template <class T>
matrix<T>::matrix(int theRows, int theCols)
{
    if (theRows < 0 || theCols < 0)
    {
        throw illegalParameterValue("行数或列数不能小于0");
    }
    //可以有0,0矩阵，但是不能有行为0但列不为0；或者列为0行不为0的矩阵
    if ((theRows == 0 || theCols == 0) && (theRows != 0 || theCols != 0))
    {
        throw illegalParameterValue("但是不能有行为0但列不为0；或者列为0行不为0的矩阵");
    }
    rows = theRows;
    cols = theCols;
    elements = new T[rews * cols];
}
template <class T>
matrix<T>::matrix(const matrix<T>& theMatrix)
{
    rows = theMatrix->rows;
    cols = theMatrix->cols;
    elements = new T[rows * cols];
    copy(theMatrix->elements, theMatrix->elements + rows * cols, elements);
}
template<class T>
T& matrix<T>::operator()(int i, int j) const
{
    return elements[(i - 1) * cols + j - 1];
}
template<class T>
matrix<T>& operator=(const matrix<T>& theMatrix)
{

}

