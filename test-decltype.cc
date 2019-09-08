#include<iostream>
#include <vector>

template<typename T>
T f();

template<typename Container>
auto getVal(Container &&cont, int idx) ->decltype(std::forward<Container>(cont)[idx]){
    return std::forward<Container>(cont)[idx];
}

int getVal(){
    int x = 10;
    return x;
}

void setVal(std::string){
}

int main(){

    /*
    int a = 0;
    f<decltype(a)>();
    f<decltype((a))>();
*/ 
    std::vector<int> intvec;
    intvec.resize(10);
    intvec[0] = 10;
    // f<decltype(getVal<std::vector<int> >(intvec, 0))>();
    // lvalue
    //getVal<std::vector<int> >(intvec, 0) = 100;
    getVal(intvec, 0) = 100;
    std::cout << "intvec[0] = " << intvec[0] << std::endl;


    std::vector<bool> boolvec(10);
    boolvec[0] = true;
    // lvalue
    // getVal<std::vector<bool> >(boolvec, 0) = false;
    getVal(boolvec, 0) = false;
    std::cout << "boolvec[0] = " << boolvec[0] << std::endl;
     
    //rvalue
    getVal<std::vector<int> >(std::vector<int>(10), 0);
    return 0;
}
