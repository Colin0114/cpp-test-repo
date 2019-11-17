#include <iostream>
#include <vector>

// See if an array is a subsequence 
// of post traversal of binary-search tree
//

bool IsSubseq(std::vector<int> &vec, int start, int len){
    auto i = start;
    auto left_len = 0;
    auto right_len = 0;

    for(; i < len-1; ){
        if( vec[i] < vec[len-1] ){
            i++;
            left_len++;
        }else{
            break;
        }
    }

    for(; i<len-1; ){
        if(vec[i] >= vec[len-1]){
            i++;
            right_len++;
        }else{
            break;
        }
    }

    if(left_len==0 && right_len==0){
        return true;
    }

    if( i < len -2){
        return false;
    }

    auto is_left = true;
    auto is_right = true;
    if(left_len){
        is_left = IsSubseq(vec, 0, left_len);
    }

    if(right_len){
        is_right = IsSubseq(vec, left_len, right_len);
    }

    return is_left && is_right;
}

int main(){
   std::vector<int> vec = {192, 14};

    auto is_subseq = IsSubseq(vec, 0, vec.size());
    if(is_subseq){
        std::cout << "it is a sub seq" << std::endl;
    }else{
        std::cout << "it is not a sub seq" << std::endl;
    }

    return 0;
}
