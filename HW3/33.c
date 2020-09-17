/*
implementation for disjoint set
���O����node����unique
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_N (ĳ�����֣��S��ÿ��node data �����ֵ����׃)
struct Node {
    struct Node * parent;
    int data;
    int dis_to_par;
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
    tmp->parent = tmp; //parent �B���Լ�
    tmp->dis_to_par = 0;
    Node_Array[new_data] = tmp;//����node array �@�ӵȵȱ��^��call
}
void Attah(int x, int y){
    struct Node * dn = Node_Array[x]; // �B������
    struct Node * up = Node_Array[y]; //�B������
    dn->parent = up;
    dn->dis_to_par = 1;
}
int Find_dis(int x){
    struct Node * tmp = Node_Array[x];
    struct Node * head = Find_Set(x);
    path_com(tmp, head); // ����parent, ����d_t_p distance to parent
    return tmp->dis_to_par + 1;
}
int del;
int Find_Set(struct Node * x){
    // x->dis_to_par �˕r == 1
    del = 1; // ���ԭ�� = 1
    if (x->parent != x){
        del += x->parent->dis_to_par;
        x->parent = Find_Set(x->parent);
    }
    return x->parent;
};
void path_com (struct Node * x, struct Node *head){
    //���¾��x //�����^
    x->parent = head;
    x->dis_to_par = del;
}

int main(){
    return 0;
}
