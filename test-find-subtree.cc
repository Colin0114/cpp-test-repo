#include <iostream>

typedef struct Node{
    int val;
    Node *left;
    Node *right;
    Node(int v){
        val = v;
        left = right = nullptr;
    }
}Node, *NodePtr;


bool PreOrderCmp(NodePtr tree1, NodePtr tree2){
    if((tree1 == nullptr) && (tree2 == nullptr)){
        return true;
    }

    if((tree1==nullptr) || (tree2==nullptr)){
        return false;
    }

    if(tree1->val == tree2->val){
        // 根据 子树来中序对比，
        return PreOrderCmp(tree1->left, tree2->left) && PreOrderCmp(tree1->right, tree2->right);
    }
   
    if(PreOrderCmp(tree1->left, tree2)){
        return true;
    }

    if(PreOrderCmp(tree1->right, tree2)){
        return true;
    }

    return false;
}

void DestroyTree(Node **tree){
    if(tree == nullptr || (*tree) ==nullptr ){
        return;
    }

    DestroyTree(&((*tree)->left));
    DestroyTree(&((*tree)->right));
    std::cout << (*tree)->val << "  \0";
    delete (*tree);
    (*tree) = nullptr;
}

void PreOrder(NodePtr tree){
    if(tree == nullptr){
        return;
    }

    std::cout << tree->val << "  ";

    PreOrder(tree->left);
    PreOrder(tree->right);
}

// tree1:
//       3
//   20     8
// 6    1 9 
//
// tree2:
//   8
//     9
int main(){
    NodePtr tree1 = new Node(3);
    tree1->left = new Node(20);
    tree1->right = new Node(8);
    tree1->left->left = new Node(6);
    tree1->left->right= new Node(1);
    tree1->right->left = new Node(9);

    NodePtr tree2 = new Node(8);
    // tree2->left = new Node(9);
    tree2->right = new Node(9);

    std::cout << "preorder tree1" << std::endl;
    PreOrder(tree1);
    std::cout << std::endl;
    std::cout << "preorder tree2" << std::endl;
    PreOrder(tree2);
    std::cout << std::endl;

    if(PreOrderCmp(tree1, tree2)){
        std::cout << "tree1 has tree2 as a subtree" << std::endl;
    }else{
        std::cout << "tree1 does not have tree2 as a subtree" << std::endl;
    }

    DestroyTree(&tree1);
    DestroyTree(&tree2);
}
