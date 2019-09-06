#include <iostream>
#include <vector>


#ifdef USE_USING
template <typename T>
using MyVec = std::vector<T>;

#else 
template<typename T>
/*
struct MyVec{
    typedef std::vector<T> vec;
};
*/
class MyVec{
public:
    typedef std::vector<T> vec;
};

#endif

int main(){
    MyVec<int>::vec myvec;

    myvec.push_back(3);    

    for_each(myvec.begin(), myvec.end(), [](int x){ std::cout<< "value is: " << x << std::endl;});

    return 0;
}
