#include <iostream>
#include <cstdlib>
#include <stack>

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
    std::cin >> data;
    if (data == 0){
        return nullptr;
    }

    NodePtr root = new Node(data);
    std::cout << "left child of node " << data << std::endl;
    root->left = CreateTree();
    std::cout << "right child of node " << data  << std::endl;
    root->right = CreateTree();
    return root;
}

void DestroyTree(Node **tree){
    if(tree == nullptr || (*tree) ==nullptr ){
        return;
    }

    DestroyTree(&((*tree)->left));
    DestroyTree(&((*tree)->right));
    std::cout << (*tree)->val << " "; 
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

void PreOrderRecursive(NodePtr tree){
    if(tree == nullptr){
        return;
    }

    std::stack<NodePtr> s;
    s.push(tree);
    NodePtr p;
    do{
       p = s.top();
       std::cout << p->val << "  " ;
       s.pop();
       if( p->right != nullptr){
            s.push(p->right);
       }
       if(p->left != nullptr){
            s.push(p->left);
       }

    }while(!s.empty());
}

void InOrder(NodePtr tree){
    if(tree == nullptr){
        return;
    }
    InOrder(tree->left);
    std::cout << tree->val << "  ";
    InOrder(tree->right);
}

void PostOrder(NodePtr tree){
    if(tree == nullptr){
        return;
    }
    PostOrder(tree->left);
    PostOrder(tree->right);
    std::cout << tree->val << "  ";
}

NodePtr FindPreNode(NodePtr tree){
    if(tree == nullptr){
        return nullptr;
    }

    // have to inorder traversal tree, and return the last visited node;
    NodePtr result = tree->left;
    while((result->right != nullptr) && (result->right != tree)){
        result = result->right;
    }
    return result;
}

void MorrisPreOrder(NodePtr tree){
    if(tree == nullptr){
        return;
    }

    NodePtr cur = tree, pre = nullptr;
    while(cur != nullptr){
        if(cur->left == nullptr){
            std::cout << cur->val << "  ";
            cur = cur->right;
        }else {
            pre = FindPreNode(cur);
            if(pre->right == nullptr){
                pre->right = cur;
                std::cout << cur->val << "  ";
                cur = cur->left;
            }else if(pre->right == cur){
                pre->right = nullptr;
                cur = cur->right;
            }
        }
    }
}

void MorrisInOrder(NodePtr tree){
    if(tree == nullptr){
        return;
    }

    NodePtr cur = tree, pre = nullptr;
    while(cur != nullptr){
        if(cur->left == nullptr){
            std::cout << cur->val << "  ";
            cur = cur->right;
        }else {
            pre = FindPreNode(cur);
            if(pre->right == nullptr){
                pre->right = cur;
                cur = cur->left;
            }else if(pre->right == cur){
                pre->right = nullptr;
                std::cout << cur->val << "  ";
                cur = cur->right;
            }
        }
    }
}

void Reverse(NodePtr from, NodePtr to){
    if(from == nullptr || to == nullptr){
        return;
    }

    if(from == to){
        return;
    }

    NodePtr pre = from;
    NodePtr cur = from->right;
    NodePtr next = nullptr;
    while(true){
        // 反转节点
        next = cur->right;
        cur->right = pre;
        if(cur == to){
            break;
        }

        // 节点前进
        pre = cur;
        cur = next;
    }
}

void PrintReversely(NodePtr from, NodePtr to){
    if(from == nullptr || to == nullptr){
        return;
    }

    Reverse(from, to);
    
    NodePtr p = to;
    while(true){
        std::cout << p->val << "  ";
        if(p == from){
            break;
        }
        p = p->right;
    }

    Reverse(to, from);
}

void MorrisPostOrder(NodePtr tree){
    if(tree == nullptr){
        return;
    }

    NodePtr cur = tree, pre = nullptr ;
    NodePtr dummy = new Node(0);
    dummy->left = tree;
    dummy->right = nullptr;

    cur = dummy;
    while(cur != nullptr){
        if(cur->left == nullptr){
            cur = cur->right;
        }else {
            pre = FindPreNode(cur);
            if(pre->right == nullptr){
                pre->right = cur;
                cur = cur->left;
            }else if(pre->right == cur){
                PrintReversely(cur->left, pre);
                pre->right = nullptr;
                cur = cur->right;
            }
        }
    }

    delete dummy;
}

int main(){

    NodePtr tree = nullptr;

    std::cout << "print the data of this node, input 0 as nullptr: " << std::endl;
    tree = CreateTree();
  
    std::cout << "先序遍历" << std::endl;
    PreOrderRecursive(tree);
    std::cout << std::endl;

    std::cout << "中序遍历" << std::endl;
    InOrder(tree);
    std::cout << std::endl;

    std::cout << "Morris InOrder traversal" << std::endl;
    MorrisInOrder(tree);
    std::cout << std::endl;

    std::cout << "后序遍历" << std::endl;
    PostOrder(tree);
    std::cout << std::endl;

    std::cout << "Morris PostOrder traversal" << std::endl;
    MorrisPostOrder(tree);
    std::cout << std::endl;
    
    std::cout << "删除树的所有节点： ";
    DestroyTree(&tree);
    std::cout << std::endl;
    return 0;
}
