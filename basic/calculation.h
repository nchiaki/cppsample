#ifndef _CALCULATION_H_
#define _CALCULATION_H_

class Calculation{
private:
    int m_number1;
    int m_number2;

public:
    void setNumber1(int n);
    void setNumber2(int n);
    int getNumber1();
    int getNumber2();
    int add(void);
    int sub(void);
};


#endif // _CALCULATION_H_
