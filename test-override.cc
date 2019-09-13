#include <iostream>

class B{
    public:
        void P(){
            std::cout << "B::P" << std::endl;
        }

        virtual void VP(){
            std::cout << "B::VP" << std::endl;
        }
};

class D:public B{
    public:
        void P(){
            std::cout << "D::P" << std::endl;
        }

        void VP() override {
            std::cout << "D::VP" << std::endl;
        }
};

class DD:public D{
    public:
        void VP() override{
            std::cout << "DD::VP()" << std::endl;
        }
};

int main(){
    D d;
    B *pb = &d;

    pb->P();            // 通过基类指针测试非虚函数：B::P
    pb->VP();           // 通过基类指针测试虚函数改写情况：D::VP
        
    d.P();              // 通过派生类对象测试非虚函数：D::P

    DD dd;
    D *pd = &dd;

    pd->VP();           // 通过基类指针测试祖先虚函数改写情况：DD:VP
    dd.VP();            // 通过派生类对象测试虚函数改写情况：DD:VP
    return 0;
}
