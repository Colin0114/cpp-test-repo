#include <iostream>
#include <initializer_list>
#include <vector>

// Tested using llvm10.0.1 

template<typename T>
void F(T t){
    
}

template<typename T>
T f();

std::vector<bool> feature(){
    return std::vector<bool>{true, false, true, true, false};
}

int main(){
    auto ia = {10};
    auto aa{1};

    F(aa);

     // f<decltype((ia))>();  // ia is std::initializer_list<int>, decltype((ia)) is std::initializer_list<int>&
    // f<decltype(aa)>(); // aa is int 


    int b = 10;
    int &r = b;
    auto ar = r; 
    auto &br = r;

     // f<decltype(ar)>(); // ar is int
    //f<decltype(br)>();  // br is int& 
    //
    
    auto fb = feature()[5];

    f<decltype(fb)>();

    return 0;
}
