#include <iostream>

class B{
    public:
        B(int b){
            b_ = b;
        }

        B(const B& b) = delete;
        B(B&& b) = default; // compile failed if commented
   private:
    int b_;
};

int main(){
    B b(10);
    B bm( std::move(b) );
    return 0;
}
