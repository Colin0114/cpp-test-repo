#include <iostream>

class All{

    private:
       int a; 
};

class ConsOnly{
    public:
        ConsOnly(int a){
        
        }
};

class DeclCopy{
    public:
        DeclCopy(){
        
        }
        
        DeclCopy(DeclCopy &d){
        
        };
};

// the Rule of Three
class DestrOnly{
    public:
        virtual ~DestrOnly(){
        
        }
        
        DestrOnly(){
        }

        DestrOnly(DestrOnly & d){
        
        }

};

int main(){

    All a;
    All b(a);
    All c( std::move(a) );

    // ConsOnly co;  // error: no matching Constructor
    
    DeclCopy d;
    DeclCopy dc(d);
    // DeclCopy dm( std::move(dc) );  // error: no matching Constructor


    DestrOnly ds;
    DestrOnly dsc(ds); // success cause the break of the Rule of Three exist in C++11
    // DestrOnly dsm(std::move(dsc)); // error: no matching Constructor, because no compiler generated move Constructor 

    return 0;
}
