#include <iostream>

#ifdef NULL
#undef NULL
#endif
#define NULL (void *)0

void Print(int){
    std::cout << "params is : int" << std::endl;
}

void Print(int *){
    std::cout << "params is : int *" << std::endl;
}

int* getPointer(){
    return nullptr;
}

int getInt(){
    return 0;
}

int main(){
    
    Print(nullptr);
    
    auto rt = getPointer();
    if( rt == 0){
        std::cout << "rt is equal 0" << std::endl;
    }else{
        std::cout << "rt is not equal 0" << std::endl;
    }

    auto rt2 = getInt();
    if(rt == nullptr){
        std::cout << "rt2 is a nullptr" << std::endl;
    }else{
        std::cout << "rt2 is not a nullptr but a integer" << std::endl;
    }

    return 0;
}

