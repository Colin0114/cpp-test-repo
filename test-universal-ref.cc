#include <iostream>

using std::cout;
using std::endl;

template<typename T>
void func(T& param) {
    cout << "传入的是左值" << endl;
}

template<typename T>
void func(T&& param) {
    cout << "传入的是右值" << endl;
}

template<typename T>
void warp(T&& param) {
    func(param);
}

int main() {
    int num = 2019;
    warp(num);
    warp(2019);

    func(num);
    func(2019);
    return 0;
}
