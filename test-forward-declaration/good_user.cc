// #include "b.h"
#include <iostream>


struct B;
struct D;

void f(B*){
    std::cout << "f B* called" << std::endl;
}

void f(void *){
    std::cout << "f void* called" << std::endl;
}


void test(D *x) { 
    f(x); 
}

