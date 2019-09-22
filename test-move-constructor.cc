#include <iostream>

class B{
    public:
        B(int b){
            pi_ = std::make_unique<int>(b);
        }

        B(const B& b){
            std::cout << "B(B& b) is called" << std::endl;
        }

        ~B(){
            std::cout << "~B(): " << *pi_ << std::endl;
        }
    private:
        std::unique_ptr<int> pi_;
};

int main(){

    B b(10);
    B bm(std::move(b)); // will core dump

    return 0;
}
