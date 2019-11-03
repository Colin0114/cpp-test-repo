#include <iostream>
#include <cstdlib>

typedef struct Node{
    int val;
    Node *left;
    Node *right;

    Node(int v){
        val = v;
    }
}Node, *NodePtr;


NodePtr CreateTree(){
    int data;
    std::cout << "print the data of this node, input 0 as nullptr: " << std::endl;
    std::cin >> data;
    if (data == 0){
        return nullptr;
    }

    NodePtr root = new Node(data);
    std::cout << "input its left child of node " << data << std::endl;
    root->left = CreateTree();
    std::cout << "input its right child of node " << data  << std::endl;
    root->right = CreateTree();
    return root;
}

void DestroyTree(Node **tree){
    if(tree == nullptr || (*tree) ==nullptr ){
        return;
    }

    DestroyTree(&((*tree)->left));
    DestroyTree(&((*tree)->right));
    std::cout << "delete node: " << (*tree)->val << std::endl;
    delete (*tree);
    (*tree) = nullptr;
}

int main(){

    NodePtr tree = nullptr;

    tree = CreateTree();

    DestroyTree(&tree);
    return 0;
}
