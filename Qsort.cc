#include <iostream>
#include <vector>

void Swap(std::vector<int> &vec, int low, int high){
    auto tmp = vec[low];
    vec[low] = vec[high];
    vec[high] = tmp; 
}

int Partition(std::vector<int> &vec, int low, int high){
    auto pivotval = vec[low];
    while(low < high){
        while(low < high && vec[high] >= pivotval)
            high--;
        Swap(vec, low, high);
        while(low < high && vec[low] <= pivotval)
            low++;
        Swap(vec, low, high);
    }

    return low;
}

void Qsort(std::vector<int> &vec, int low, int high){
    if(low < high){
        int pivot = Partition(vec, low, high);
        Qsort(vec, low, pivot);
        Qsort(vec, pivot+1, high);
    }
}

void Print(std::vector<int> &vec){
    std::vector<int>::iterator iter = vec.begin();
    while(iter != vec.end()){
        std::cout << *iter << "  ";
        iter++;
    }

    std::cout << std::endl;
}

int main(){
    std::vector<int> vec = {1, 8, 10, 2, 3, 7, 4, 9, 6}; 

    Print(vec);

    Qsort(vec,0, vec.size()-1);

    Print(vec);

    return 0;
}
