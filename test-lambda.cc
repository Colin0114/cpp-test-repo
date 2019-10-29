#include <iostream>

void test_lambda_size(){
    auto doub_var = 8.001;
    auto int_var = 4;
    auto lambda_cap_double = [doub_var](){ std::cout << "val is: " << doub_var << std::endl; };
    auto lambda_cap_int = [int_var](){ std::cout << "val is: " << int_var << std::endl; };

    auto lambda_cap_ref_double = [&doub_var](){ std::cout << "val is: " << doub_var << std::endl; };
    auto lambda_cap_ref_int = [&int_var](){ std::cout << "val is: " << int_var << std::endl; };

    std::cout << "size of lambda captruing one ref double: " << sizeof(lambda_cap_ref_double) << std::endl; // output 8, undefined behavior
    std::cout << "size of lambda captruing one ref int: " << sizeof(lambda_cap_ref_int) << std::endl; // output 8, undefined behavior

    std::cout << "size of lambda captruing one double: " << sizeof(lambda_cap_double) << std::endl; // output 8
    std::cout << "size of lambda captruing one int: " << sizeof(lambda_cap_int) << std::endl; // output 4

}

int main(){
    auto print_hello = []{ std::cout << "hello world" << std::endl; };

    print_hello(); 
    test_lambda_size();
    return 0;
}
