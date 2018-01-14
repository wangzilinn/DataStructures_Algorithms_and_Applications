#pragma once
class illegalParameterValue
{
public:
    illegalParameterValue() :
        message("非法的参数值") {}
    illegalParameterValue(char * theMessage)
    {
        message = theMessage;
    }
    void outputMassage();
private:
    string message;
};
template<class T>
void displayArray(T a[], int arrayLength)
{
    for (int i = 0; i < arrayLength; i++)
    {
        cout << a[i] <<" ";
    }
    cout << endl;
}