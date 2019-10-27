#include <iostream>
#include <stack>

typedef struct Node{
    int val;
    Node *next;
}Node;

void AddToTail(Node** list, int val){
    if(list == nullptr){ //头指针本身为空
        std::cout << "empty list" << std::endl;
    }
    Node *pnode = new Node;
    pnode->val = val;
    pnode->next = nullptr;

    if(*list == nullptr){ // 头结点为空，即空链表
        *list = pnode;
        return;
    }

    Node *p = *list;
    while(p->next != nullptr){ // 这里的终止条件不能为 p!=nullptr, 否则无法插入
        p = p->next;
    }

    p->next = pnode;
}

void DestroyList(Node **list){
    if(list==nullptr || *list==nullptr){
        std::cout << "empty list" << std::endl;
        return;
    }

    Node *pre = *list, *next=*list;
    int count = 0;
    while(pre!=nullptr){ // 这里的终止条件是否可以为 pre->next !=nullptr?
        next = pre->next; // 必须先获取下一个节点的地址，才能释放当前节点的内存
        delete pre;
        pre = next;
        count ++;
    }
    
    list = nullptr;
    std::cout << "nodes deleted: " << count << std::endl;
}

void PrintList(Node *list){
    if(list==nullptr){
        std::cout << "empty list" << std::endl;
        return;
    }
    
    Node *p = list;
    int count = 0;
    while(p!=nullptr){
        std::cout << p->val << " " ;
        p = p->next;
        count++;
    }

    std::cout << std::endl << "nodes printed: " << count << std::endl;
}

void PrintListReversely(Node *list){
    if(list == nullptr){
        return;
    }

    PrintListReversely(list->next);
    std::cout << list->val << "" << std::endl;
}

void PrintListReverselyUsingStack(Node *list){
    Node *p = list;
    std::stack<Node *> nodes;
    while(p != nullptr){
        nodes.push(p);
        p = p->next;
    }

    while( !nodes.empty()){
       p = nodes.top();
       nodes.pop();
       std::cout << p->val<< " " ;
    }

    std::cout << std::endl;
}

void RemoveNode(Node **list, int val){
    if(list == nullptr || *list == nullptr){
        std::cout << "empty list" << std::endl;
        return;
    }

    Node *p = *list, *pre = *list;
    while(p!= nullptr){ // 这里的终止条件是否可以设为 p->next != nullptr?
        if(p->val == val){
            // 如果是头结点，则需要特殊处理, 但把判断放在这里不妥，
            // 因为增加了判断，头结点只需要单独多写几行代码处理即可
            p==*list? *list=p->next : pre->next= p->next;
            delete p; 
        }
        pre = p;
        p = p->next;
    }
}

void RemoveNode2(Node **list, int val){
    if(list == nullptr || *list == nullptr){
        std::cout << "empty list" << std::endl;
        return;
    }

    Node *node_to_delete = nullptr;
    if((*list)->val == val){
        node_to_delete = *list;
        *list = (*list)->next;
        return;
    }
    
    Node *p = (*list)->next, *pre = *list;
    while(p!=nullptr){
        if(p->val == val){
            pre->next = p->next;
            node_to_delete = p;
        }
        pre = p;
        p = p->next;
    }

    if(node_to_delete != nullptr){
        delete node_to_delete;
    }
}

void RemoveNodeInO1(Node **list, Node *to_delete){
    if( list==nullptr || *list==nullptr || to_delete==nullptr)
        return;
   // 删除节点为头结点，直接删除，并把链表置空
   if(to_delete == (*list)){
       delete to_delete;
       *list=nullptr;
       to_delete = nullptr;
   } 

   // 如果是链表的最后一个节点，则需要遍历到尾节点的前一个节点，才能删除
   if(to_delete->next != nullptr){
        to_delete->val = to_delete->next->val;
        to_delete->next = to_delete->next->next;
        return;
   }

   Node *p = *list;
   // 这里表示一定能在链表中找到 to_delete，否则会出错
   while(p->next != to_delete && p->next !=nullptr){
       p = p->next;
   }
   
   if(p->next == nullptr && p != to_delete){
       std::cout << "cannot find the node to delete: " << to_delete->val << std::endl;
       return;
   }   
  
   p->next = to_delete->next;
   delete to_delete;
   to_delete = nullptr;
}

void PrintReverseKnode(Node *list, int k){
    if( list == nullptr){
        std::cout << "empty list" << std::endl;
        return;
    }

    Node *pre = list, *p = list;
    int count = 0;
    while(p!=nullptr && count < k){
        p = p->next;
        count++;
    }

    if(p==nullptr && count < k){
        std::cout << "list not long enough" << std::endl;
        return;
    } 

    while(p != nullptr){
        pre = pre->next;
        p = p->next;
    }

    std::cout << "the reverse "<< k << "th node: " << pre->val << std::endl;
}

int main(){
    Node *list = nullptr;

    AddToTail(&list, 10);
    AddToTail(&list, 0);
    AddToTail(&list, 1);
    //PrintListReverselyUsingStack(list);
    PrintReverseKnode(list, 2);
    // PrintList(list);
    // RemoveNode(&list, 0);

    DestroyList(&list);
    return 0;
}
