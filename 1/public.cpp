#include "stdafx.h"
void illegalParameterValue::outputMassage(ostream & out) const
{
    out << message;
}
void illegalParameterValue::outputMassage() const
{
    cout << message << endl;
}
ostream & operator<<(ostream & out, const illegalParameterValue & err)
{
    err.outputMassage(out);
    return out;
}