#include <iostream>
#include <climits>
#include <stack>
#include <queue>

typedef struct Node{
    int val;
    Node *left;
    Node *right;
    Node(int v){
        val = v;
        left = right = nullptr;
    }

}Node, *NodePtr;

// Method 1: can get both max or min depth
void GetTreeDepth(NodePtr tree, int & cur_depth, int &max_depth, int &min_depth){
    if(tree == nullptr){
        return ;
    }

    cur_depth++;
    bool is_leaf = tree->left == nullptr && tree->right == nullptr;
    if(is_leaf && cur_depth > max_depth){
        max_depth = cur_depth;
    }
    if(is_leaf && min_depth > cur_depth){
        min_depth = cur_depth;
    }

    GetTreeDepth(tree->left, cur_depth, max_depth, min_depth);
    GetTreeDepth(tree->right, cur_depth, max_depth, min_depth);
    cur_depth--;
}

// Method 2, can only get depth 
int TreeDepth(NodePtr tree){
    if(tree == nullptr){
        return 0;
    }

    int left = TreeDepth(tree->left);
    int right = TreeDepth(tree->right);

    return left>right?left+1:right+1;
}

// 后序删除树，保证最后删除的是根节点
void DestroyTree(Node **tree){
    if((tree ==nullptr) || (*tree==nullptr)){
        return;
    }

   DestroyTree(&((*tree)->left)); 
   DestroyTree(&((*tree)->right)); 

   std::cout << (*tree)->val <<"  ";
   delete (*tree);
   *tree = nullptr;
   tree = nullptr;
}

// Method 3: layer traversal
int TreeDepthByLayerTraversal(NodePtr tree){
    if( !tree ){
        return 0;
    }
    int depth = 0;
    int mark_cur = 1;
    int mark_next = 0;
    NodePtr ptr = nullptr;
    std::queue<NodePtr> q;
    q.push(tree);
    while(!q.empty()){
        ptr = q.front();
        q.pop(); 
        mark_cur --;

        if(ptr->left){
            mark_next++;
            q.push(ptr->left);
        }
        if(ptr->right){
            mark_next++;
            q.push(ptr->right);
        }

        if(mark_cur == 0){
            depth ++;
            mark_cur = mark_next;
            mark_next = 0;
        }
    }

    return depth;
}

int main(){
    NodePtr tree = new Node(1);
    tree->left = new Node(8);
    tree->right = new Node(9);
    tree->left->left = new Node(16);
    tree->left->right = new Node(2);
    tree->left->right->right = new Node(5);
    tree->left->right->right->left = new Node(8);
    tree->right->left = new Node(7);
    tree->right->left->right = new Node(7);
    tree->right->left->right->left = new Node(7);
    tree->right->left->right->left->left = new Node(7);

    auto cur_depth = 0;
    auto max_depth = 0;
    auto min_depth = INT_MAX;
    GetTreeDepth(tree, cur_depth, max_depth, min_depth);
    std::cout << "the max depth of tree is: " << max_depth << std::endl;
    std::cout << "the min depth of tree is: " << min_depth << std::endl;

    auto depth = TreeDepthByLayerTraversal(tree);
    std::cout << "tree depth counted by TreeDepthByLayerTraversal: " << depth << std::endl;

    std::cout << "deleting tree" << std::endl;
    DestroyTree(&tree);
    std::cout << std::endl;

    return 0;
}
