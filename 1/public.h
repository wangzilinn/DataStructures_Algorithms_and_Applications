#pragma once
class illegalParameterValue
{
public:
    illegalParameterValue() :
        message("�Ƿ��Ĳ���ֵ") {}
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