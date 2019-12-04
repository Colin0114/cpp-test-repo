#include <iostream>

class A{
    public:
        A(int val){
            val_ = val;
        }
        ~A(){
           std::cout << "A is destructed" << std::endl;
        }

    void Print(){
        std::cout << "val is: " << val_ << std::endl;
    }
    private:
        int val_;
};


// output:
// 20
// 20
// A is destructed
// A is destructed

int main(){
    A a(20);

    a.Print();
    A b = std::move(a);

    b.Print();

    return 0;
}
