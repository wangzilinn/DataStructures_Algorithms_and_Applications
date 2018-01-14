#pragma once
//17
enum signType{cplus = 0, cminus};
class currency
{
public:
    currency(signType theSign = cplus, unsigned long theDollors = 0, unsigned int theCents = 0);
    ~currency();
    void setValue(signType, unsigned long, unsigned int);
    void setValue(double);
    unsigned long getDollors() const;
    unsigned int getCents() const;
    signType getSign() const;
    currency add(const currency&) const;
    currency& increment(const currency&);
    void input();
    currency subtract(long);
    void output() const;
private:
    long amount;
};

