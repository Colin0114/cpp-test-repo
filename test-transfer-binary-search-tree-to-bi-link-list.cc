#include <iostream>

typedef struct Node{
    int val;
    Node *left; //pre 
    Node *right; //post
    Node(int v){
        val = v;
        left = right = nullptr;
    }
}Node, *NodePtr;

NodePtr FindPreNode(NodePtr tree){
   if(!tree){
       return tree;
   } 

   NodePtr pre = tree;
   while((pre->right!=nullptr) && (pre->right!=tree)){
        pre = pre->right;
   }

   return pre;
}

NodePtr FindPostNode(NodePtr tree){
    if(tree == nullptr){
        return tree;
    }

    auto ptr = tree;
    while(ptr->left != nullptr){
        ptr = ptr->left;
    }

    return ptr;
}

void LinkTree(NodePtr start, NodePtr end){
    auto cur = start;
    auto pre = start;
    auto next = start;
    while(cur!=nullptr && cur != end){
        pre = FindPreNode(cur->left);
        if(pre->right == nullptr){
            pre->right = cur;
        }
        next = cur->left;
        cur->left = nullptr;
        cur = next; 
    }
}

NodePtr ToBilinkList(NodePtr tree){
    if(!tree){
        return nullptr;
    }

    NodePtr head = nullptr;
    head = FindPostNode(tree);
    auto cur = tree;
    LinkTree(cur, head);

    auto post = cur;
    while(!cur){
        post = FindPostNode(cur->right);
        if(post){
            // 把 cur 的右子树进行线索化处理
            LinkTree(cur->right, post);
            cur->right = post;
            post->left = cur;
            cur = cur->right;
        }else{
            cur->right->left = cur; // right 的 pre 是 cur，cur 的 post 是 right
            cur = cur->right;
        }
    }

    return head;
}

void DestroyTree(NodePtr tree){
    auto next = tree;
    while(tree){
        std::cout << tree->val << "  ";
        next = tree->right;
        delete tree;
        tree = next;
    }
}
int main(){
    // binary search tree 
    NodePtr tree = new Node(20);
    tree->left = new Node(15); // 20's left and right 
    tree->right = new Node(30);
    tree->left->left = new Node(13); // 15's left and right 
    tree->left->right = new Node(18);
    tree->left->left->left = new Node(11); // 13's left and right 
    tree->left->left->right = new Node(14);
    tree->left->right->left = new Node(17); // 18's left and right 
    tree->left->right->right = new Node(19);
    tree->right->left = new Node(21);

    auto list = ToBilinkList(tree);

//    PrintList(list);

    std::cout << "deleting list" << std::endl;
    DestroyTree(list);
    std::cout << std::endl;
    return 0;
}
