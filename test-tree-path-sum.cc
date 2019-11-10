#include <iostream>
#include <vector>

typedef struct Node{
    int val;
    Node *left;
    Node *right;
    Node(int v){
        val = v;
        left = right = nullptr;
    }
}Node, *NodePtr;

void DestroyTree(Node **tree){
    if(tree ==nullptr || *tree == nullptr){
        return;
    }

    DestroyTree(&((*tree)->left));
    DestroyTree(&((*tree)->right));
    std::cout << (*tree)->val << "  ";
    delete *tree;
    *tree = nullptr;
}   

void PrintVec(std::vector<int> &vec){
    for_each(vec.begin(), vec.end(), [](auto iter){ std::cout << iter << "  "; });
    std::cout << std::endl;
}

void FindPath(NodePtr tree,std::vector<int> &vec, int sum, int &cur_sum){
    if(tree == nullptr){
        return;
    }

    vec.push_back(tree->val);
    cur_sum += tree->val;
    if(tree->left ==nullptr && tree->right==nullptr){
        if(cur_sum == sum){
            PrintVec(vec); 
        }    
    }
    FindPath(tree->left, vec, sum, cur_sum);
    FindPath(tree->right, vec, sum, cur_sum);
    vec.pop_back();
    cur_sum -= tree->val;
}

void FindPath(NodePtr tree, int sum){
    std::vector<int> vec;
    int cur_sum = 0;
    FindPath(tree, vec, sum, cur_sum);
}

int main(){
    int sum;
    std::cout << "input the sum you want: " << std::endl;
    std::cin >> sum;
    
    NodePtr tree = new Node(10);
    tree->left = new Node(5);
    tree->right = new Node(12);
    tree->left->left = new Node(4);
    tree->left->right = new Node(7);

    FindPath(tree, sum);

    std::cout << "deleting tree" << std::endl;
    DestroyTree(&tree);
}
