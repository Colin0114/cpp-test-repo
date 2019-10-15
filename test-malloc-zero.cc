#include <iostream>

int main(){
    void *p = nullptr;
    p = malloc(0); // it is a undefined behavior according to C specification

    std::cout << "addr of p = malloc(0) is:" << p << std::endl; // what will output: nullptr or non-nullptr?

    char *q = static_cast<char *>(p);
    q[0] = 'a';
    q[1] = 'b';
    q[2] = '\0';

    q[1024000] = '*';


    std::cout << "q is:" << q << std::endl; // what will happen, segmentfault or output "ab"
    free(p);
    return 0;
}
