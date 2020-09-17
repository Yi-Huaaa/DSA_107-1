#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_N 10000//這個最後要改

struct Node {
    struct Node * parent;
    int data;
    int rank;
};
struct Node * create_Node (void){
    struct Node * New_node = (struct Node*)malloc(sizeof(struct Node));
    if(New_node == NULL)
        exit(1);
    return (New_node);
};

struct Node * Node_Array [MAX_N];
void Make_Set (int new_data){
    struct Node * tmp = create_Node();
    tmp->data = new_data;
    tmp->parent = tmp; //parent 連到自己
    tmp->rank = 0;
    Node_Array[new_data] = tmp;//存入node array 這樣等等比較好call
}
void Union(int x, int y){
    struct Node * n_x = Node_Array[x];
    struct Node * n_y = Node_Array[y];
    Link(Find_Set(n_x),Find_Set(n_y));
};
void Link(struct Node * x, struct Node * y){
    if (x->rank > y->rank){
        y->parent = x;
    }
    else {
        x->parent = y;
        if (x->rank == y->rank){
            y->rank = y->rank + 1;
        }
    }
}
bool jdg;
int dat;
struct Node * Find_Set(struct Node * x){
    dat = 0;
    if (x->data != -1)
        dat = x->data;
    jdg = false;
    //若讀到 -1 == -1則要回傳前一個
    if (x->parent != x){
        x->parent = Find_Set(x->parent);
    }
    if(x->parent->data == -1 && x->data == -1){
        jdg = true;
    }
    if (jdg == false)
        return x->parent;
    else // 讀到 -1 == -1，代表頭之前被刪掉了
        return Node_Array[dat];
};
//跟上面不一樣的是要更新rank
struct Node *Find_Set_for_delete(struct Node * x){
    dat = 0;
    if (x->data != -1)
        dat = x->data;
    jdg = false;

    //去除之前被刪掉的點
    if (x->parent->data == -1){
        //遇到之前刪中間的狀況，重新接頭
        x->parent = x->parent->parent;
        //遇到之前刪掉頭的狀況
        if (x->parent->parent->data == -1){
            x->parent = x;
        }
    }
    //更新rank
    x->rank --;
    if (x->parent != x){
        x->parent = Find_Set_for_delete(x->parent);
    }
    if(x->parent->data == -1 && x->data == -1){
        jdg = true;
    }
    if (jdg == false)
        return x->parent;
    else
        return Node_Array[dat];
};

void Isolate(int k){
    struct Node * del_node = Node_Array[k];
    del_node->data = -1; //將data設為-1，之後找parent遇到-1時，就繼續往上找

    // 純粹更新rank用
    struct Node * head = Find_Set_for_delete(del_node);

    //Node_Array裡面的Node也會被新的Node蓋掉
    Make_Set(k);//重新new這個data成一個新的Node
}

bool Same_Set (int x, int y){
    struct Node * x = Node_Array[x];
    struct Node * y = Node_Array[y];
    if (Find_Set(x) == Find_Set(y))
        return true;
    else
        return false;
}


int main()
{
}
