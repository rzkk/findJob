#include "mycomplex.h"
// #include "myinline.hpp"
#include<iostream>
namespace math_Fun{

void Complex::showComplex()
{
    std::cout<<real<<" + "<<image<<"i \n";
}
}