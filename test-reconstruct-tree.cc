#include <iostream>
#include <array>

typedef struct Node{
    int val;
    Node *left;
    Node *right;
    Node(int v){
        val = v;
        left = right = nullptr;
    }
}Node, *NodePtr;

NodePtr ConstructCore(int *pre_order_start, int *pre_order_end, int *in_order_start, int *in_order_end){
    NodePtr root = new Node(*pre_order_start);
    if(pre_order_start == pre_order_end){
        if(in_order_start == in_order_end && *pre_order_start == *in_order_start){
            return root;
        }

        std::cout << "invalid sequence, the current pre_order_start is: " << *pre_order_start << std::endl;
        return nullptr;
    }

    int *p = in_order_start;
    int left_length = 0;
    while(*p != *pre_order_start){
        p ++;
        left_length ++;
    }
    int right_length = 0;
    while(p != in_order_end){
        p ++;
        right_length ++;
    }

    if(left_length > 0){
        root->left = ConstructCore(pre_order_start+1, pre_order_start+left_length, in_order_start, in_order_start+left_length-1);
    }
    if(right_length > 0){
        root->right = ConstructCore(pre_order_start+left_length+1, pre_order_end, in_order_start+left_length+1, in_order_end);
    }

    return root;
}

NodePtr ReConstruct(int *pre_order_arr, int* in_order_arr, int length){
    return ConstructCore(pre_order_arr, pre_order_arr+length-1, in_order_arr, in_order_arr+length-1);
}


void DestroyTree(Node ** tree){
    if(tree == nullptr || (*tree)==nullptr){
        return;
    }
    DestroyTree(&((*tree)->left));
    DestroyTree(&((*tree)->right));
    std::cout << (*tree)->val << "  ";
    delete *tree;
    *tree = nullptr;
}

int main(){
    std::array<int, 8> pre_order_arr = {1, 2, 4, 7, 3, 5, 6, 8};
    std::array<int, 8> in_order_arr = {4, 7, 2, 1, 5, 3, 8, 6};
    NodePtr reconstructed_tree;
    reconstructed_tree = ReConstruct(pre_order_arr.data(), in_order_arr.data(), pre_order_arr.size());

    std::cout << "deleting tree" << std::endl;
    DestroyTree(&reconstructed_tree);
    std::cout << std::endl;
    return 0;
}
