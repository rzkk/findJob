#ifndef _COMPLEX_H_
#define _COMPLEX_H_

namespace math_Fun{
class Complex{
public:
    Complex(int x = 0, int y = 0):real(x), image(y){}
    ~Complex(){}
    void showComplex();
private:
    int real;
    int image; 
};
}


#endif