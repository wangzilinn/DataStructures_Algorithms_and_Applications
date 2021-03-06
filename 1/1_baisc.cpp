// 1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//3
template <class T>
void fill(T *a, int start, int end, const T &value)
{
    for (int i = start; i < end; i++)
    {
        a[i] = value;
    }
}
//5
template <class T>
void iota(T *a, int &n, T & value)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = value + i;
    }
}
//7
template <class T>
int  mismatch(T *a, T *b, T aLength, T bLength)
{
    for (int i = 0; (i < aLength) && (i < bLength); i++)
    {
        if (a[i] != b[i])
            return i;
    }
    return (aLength > bLength ? aLength : bLength);
}
int abc(int a, int b, int c)
{
    if (a <= 0 && b <= 0 && c <= 0)
    {
        throw "全为负数";
    }
    return a + b + c;
}
//create 2d array
template <class T>
void make2dArray(T** &a, int numberOfCols, int numberOfRows)
{
    //创建行指针：
    a = new T* [numberOfRows];
    for (int i = 0; i < numberOfRows; i++)
    {
        a[i] = new T[numberOfCols];
    }
}
//delete 2d array
template <class T>
void delete2dArray(T** &a, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; i++)
    {
        delete[] a[i];//先释放每一行的空间
    }
    delete[] a;//再删除指向指针的指针
    a = nullptr;
}
//13
template <class T>
void change1dArrayLength(T*&a, int oldLength, int newLength)//第一个参数写T* a也行
{
    T* temp = new T[newLength];
    for (int i = 0; i < oldLength && i < newLength; i++)
    {
        temp[i] = a[i];
    }
    delete[] a;
    a = temp;
}
//17
currency::currency(signType theSign, unsigned long theDollors, unsigned int theCents)
{
    setValue(theSign, theDollors, theCents);
}
currency::~currency()
{
}
void currency::setValue(signType theSign, unsigned long theDollors, unsigned int theCents)
{
    if (theCents >= 100)
        throw illegalParameterValue("美分不能超过99");
    amount = theDollors * 100 + theCents;
    if (theSign == cminus)
        amount = -amount;
}
void currency::setValue(double theAmount)
{
    if (theAmount < 0)
    {
        amount = (long)((theAmount - 0.001) * 100);
    }
    else
    {
        amount = (long)((theAmount + 0.001) * 100);//加0.001的目的是防止出现0.99变为0的情况
    }
}
signType currency::getSign() const
{
    if (amount > 0)
        return cplus;
    else
        return cminus;
}
currency currency::add(const currency & x) const
{
    currency temp;
    temp.amount = amount + x.amount;//成员函数可以访问相同类型的其他对象的私有成员
    return temp;
}
currency & currency::increment(const currency & x)
{
    amount = x.amount;
    return *this;//this本来是指针，返回了引用
}
void currency::input()
{
    cout << "输入美分数" << endl;
    long temp;
    cin >> temp;
    setValue(temp);
}
currency currency::subtract(long x)
{
    amount -= x;
    return *this;
}
void currency::output() const
{
    long theAmount = amount;
    if (theAmount < 0)
    {
        theAmount = -theAmount;
        cout << '-' << theAmount << endl;
    }
    else
    {
        cout << '+' << theAmount << endl;
    }
}
unsigned long currency::getDollors() const
{
    if (amount > 0)
        return amount / 100;
    else
        return (-amount) / 100;
}
unsigned int currency::getCents() const
{
    if (amount > 0)
        return amount - getDollors() * 100;
    else
        return -amount - getDollors() * 100;
}
//eg 1-3
template <class T>
void permutations(T list[], int k, int m)
{
    //生成所有排列：
    if (k == m)//仅有一组排列直接输出
    {
        copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
        cout << endl;
    }
    else
    {
        for (int i = k; i <= m; i++)
        {
            swap(list[k], list[i]);//让该数组的每个元素都能在本层首位一次
            permutations(list, k + 1, m);
            swap(list[k], list[i]);//恢复交换之前的状态
        }
    }
}
//19
int factorial(int x)
{
    if (x <= 1)
        return 1;
    int ret = 1;
    for (int i = 1; i <= x; i++)
    {
        ret *= i;
    } 
    return ret;
}
//21.3
int fun21(int x)
{
    if (x % 2 == 0)
        return x / 2;
    else
    {
        fun21(3 * x + 1);
    }
    return 0;//只是防止警告
    //return (3 * n + 1) / 2 //非递归
}
//learn function pointer
class CTestFun
{
protected:
	typedef void(*PFunction_one)();
	//function instance
	static void function_one_instance()
	{
		cout << "I am function one instance" << endl;
	}
	//function user
	void function_one_user(PFunction_one function)
	{
		function();
	}
	typedef bool(CTestFun::*PFunction_two)(int);
	//function instance
	bool function_two_instance(int a)
	{
		cout << "I am function two instance" << endl;
		return true;
	}
	bool function_two_user(PFunction_two function)
	{
		if ((this->*function)(1) == true)
			return false;
		return true;
	}
public:
	void testFunction()
	{
		//function_one_user(function_one_instance);
		function_two_user(&CTestFun::function_two_instance);
	}
};

int main()
{
	try
	{
		testAt15();
	}
	catch (illegalParameterValue err)
	{
		cout << err;
	}
	return 0;
}
 
