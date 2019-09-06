#include <cstdio>

class Base{
public:
    virtual void Print(){
        printf("Base Print\n");
    }
};

class Derived:public Base{
    public:
        virtual void Print(){
            printf("Derived Print\n");
        }
    
};

int main(){
    Base *pB = new Derived();

    pB->Print();

    delete pB;
    return 0;
}
