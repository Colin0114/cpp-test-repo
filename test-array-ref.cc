#include <iostream>

template<typename T>
void F(T t, int idx){
    t[idx] = '*';
    std::cout << "F with non-ref array called" << std::endl;
}

template<typename T, std::size_t N>
void F(T (&t)[N], int idx){
    t[idx] = '*';
    std::cout << "F with ref array called , array size: " << N << std::endl;
}

int main(){
    char n[11] = "helloworld";
    char *p ;
    p = new char(11);
    memcpy(p, "1234567890", 10);

    F(p, 5);
    std::cout << "(1) p is: " << p << std::endl;
    F(n, 5);
    std::cout << "(2) n is: " << n << std::endl;

    return 0;
}
