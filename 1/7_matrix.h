#pragma once
template <class T>
class matrix
{
private:
    int rows;//行数
    int cols;//列数
    T * elements;
public:
    matrix(const int theRows = 0, const int theCols = 0);
    matrix(const matrix<T>&);
    matrix(const int theRows, const int thrCols, const T* matrixArray);
    ~matrix() { delete[] elements; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    T& operator()(int i, int j) const;//done
    matrix<T>& operator=(const matrix<T>&);//done
    matrix<T> operator+(const matrix<T>&);//done
    matrix<T> operator-(const matrix<T>&);//done
    matrix<T> operator-() const;//done
    matrix<T> operator*(const matrix<T>&);//done
    matrix<T>& operator+=(const matrix<T>&);//done
    void output(ostream& out) const;//done
};
template<class T>
matrix<T>::matrix(const int theRows, const  int theCols, const T* matrixArray)
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
    elements = new T[rows * cols];
    copy(matrixArray, matrixArray + theCols * theRows, elements);
}
template <class T>
matrix<T>::matrix(const int theRows, const int theCols)
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
    elements = new T[rows * cols]();
}
template <class T>
matrix<T>::matrix(const matrix<T>& theMatrix)
{
    rows = theMatrix.rows;
    cols = theMatrix.cols;
    elements = new T[rows * cols];
    copy(theMatrix.elements, theMatrix.elements + rows * cols, elements);
}
template<class T>
T& matrix<T>::operator()(int i, int j) const
{
    return elements[(i - 1) * cols + j - 1];
}
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& theMatrix)
{
    if (this != &theMatrix)
    {
        delete [] elements;
        rows = theMatrix.rows;
        cols = theMatrix.cols;
        elements = new T[rows * cols];
        copy(theMatrix.elements, theMatrix.elements + rows * cols, elements);
    }
    return *this;
}
template <class T>
matrix<T> matrix<T>::operator+(const matrix<T>& theMatrix)
{
    //检查参数
    if ((rows != theMatrix.rows) || cols != theMatrix.cols)
    {
        throw illegalParameterValue("两个矩阵必须行列相等");
    }
    matrix<T> returnMatrix(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        returnMatrix.elements[i] = elements[i] + theMatrix.elements[i];
    }
    return returnMatrix;
}
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& theMatrix)
{
    //检验这两个矩阵是否能够相乘：
    if (cols != theMatrix.rows)
    {
        throw illegalParameterValue("两个矩阵不能相乘");
    }
    //计算结果矩阵的行数和列数：
    int resultRows = rows;
    int resultCols = theMatrix.cols;
    matrix<T> resultMatrix(resultRows, resultCols);
    for (int i = 1; i <= resultRows; i++)//i是行
    {
        for (int j = 1; j <= resultCols; j++)//j是列
        {
            for (int k = 1; k <= cols; k++)
            {
                //resultMatrix(i, j) = resultMatrix(i, j) + (*this)(i, k) * theMatrix(k, j);
                T temp = (*this)(i, k) * theMatrix(k, j);
                resultMatrix(i, j) += temp;
            }            
        }
    }
    return resultMatrix;
}
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& theMatrix)
{
    //检查是否能够相减：
    if (rows != theMatrix.rows || cols != theMatrix.cols)
    {
        throw illegalParameterValue("两个矩阵行列不同，不能相减");
    }
    matrix<T> returnMatrix(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        returnMatrix.elements[i] = elements[i] - theMatrix.elements[i];
    }
    return returnMatrix;
}
template<class T>
matrix<T> matrix<T>::operator-() const
{
    matrix<T> returnMatrix(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        returnMatrix.elements[i] = -elements[i];
    }
    return returnMatrix;
}
template <class T>
matrix<T>& matrix<T>::operator+=(const matrix<T>& thrMatrix)
{
    //检查是否能相加
    if (rows != thrMatrix.rows || cols != thrMatrix.cols)
    {
        throw illegalParameterValue("两个矩阵行列不同，不能复合相加");
    }
    for (int i = 0; i < rows * cols; i++)
    {
        elements[i] += thrMatrix.elements[i];
    }
    return (*this);
}
template <class T>
void matrix<T>::output(ostream& out) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out << elements[i * cols + j] << " ";
        }
        out << "\n";
    }
}
template <class T>
ostream& operator<<(ostream& out, const matrix<T> &x)
{
    x.output(out);
    return out;
}

