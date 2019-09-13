#include <iostream>

#ifdef NULL
#undef NULL
#endif
#define NULL 0


void Print(int){
    std::cout << "params is : int" << std::endl;
}


void Print(int *){
    std::cout << "params is : int *" << std::endl;
}

void Print(void *){
    std::cout << "params is : void *" << std::endl;
}


int main(){
    
    Print(NULL);
    
    auto rt = nullptr;
    if( rt == 0){
        std::cout << "rt is equal 0" << std::endl;
    }else{
        std::cout << "rt is not equal 0" << std::endl;
    }

    auto tmp = 10;
    Print(&tmp);
    return 0;
}

