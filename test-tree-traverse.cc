#include <iostream>
#include <cstdlib>
#include <stack>

typedef struct Node{
    int val;
    Node *left;
    Node *right;

    Node(int v){
        val = v;
        left = right = nullptr;
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

void PreOrderRecursive(NodePtr tree){
    std::stack<NodePtr> s;
    NodePtr p = tree;
    while( p !=nullptr || !s.empty()){
        while(p !=nullptr){
            std::cout << p->val << "  ";
            s.push(p);
            p = p->left;
        }
        if( !s.empty() ){
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
}

void InOrderRecursive(NodePtr tree){
    std::stack<NodePtr> tstack;
    NodePtr cur = tree;
    while( cur != nullptr || !tstack.empty() ){
        while(cur != nullptr){
            tstack.push(cur);
            cur = cur->left;
        }

        if( !tstack.empty() ){
            cur = tstack.top();
            std::cout << cur->val <<"  ";
            tstack.pop();
            cur = cur->right;
        }
    }
}

void PostOrderRecursive(NodePtr tree){
    if(tree == nullptr){
        return;
    }

    std::stack<NodePtr> tstack;
    NodePtr cur = tree, pre = nullptr;
    tstack.push(tree);
    while(!tstack.empty()){
        cur = tstack.top();
        if( (cur->left ==nullptr && cur->right==nullptr) ||
                (pre!=nullptr && (cur->left == pre || cur->right == pre))){
            std::cout << cur->val << "  ";
            tstack.pop();
            pre = cur;
        }else{
            if(cur->right){
                tstack.push(cur->right);
            }

            if(cur->left){
                tstack.push(cur->left);
            }
        }
    }
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
  
    std::cout << "迭代先序遍历" << std::endl;
    PreOrderRecursive(tree);
    std::cout << std::endl;

    std::cout << "中序遍历" << std::endl;
    InOrder(tree);
    std::cout << std::endl;

    std::cout<< "迭代式中序遍历" << std::endl;
    InOrderRecursive(tree);
    std::cout << std::endl;
     
    std::cout << "Morris InOrder traversal" << std::endl;
    MorrisInOrder(tree);
    std::cout << std::endl;

    std::cout << "迭代后序遍历" << std::endl;
    PostOrderRecursive(tree);
    std::cout << std::endl;

    std::cout << "Morris PostOrder traversal" << std::endl;
    MorrisPostOrder(tree);
    std::cout << std::endl;

    std::cout << "删除树的所有节点： ";
    DestroyTree(&tree);
    std::cout << std::endl;
    return 0;
}
