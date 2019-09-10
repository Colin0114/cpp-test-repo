#include <iostream>

template<typename T>
void F(T p){
    std::cout << "p in F before modified:" << p << std::endl;
    const char* ptr = "nihao";
    p = ptr;
    
    std::cout << "p in F after modified:" << p << std::endl;
}

int main(){

    const char* const p = "helloworld";

    F(p);

    std::cout << "p in main:" << p << std::endl;

    return 0;
}
