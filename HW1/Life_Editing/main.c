/*
Reference :
1.https://lakesd6531.pixnet.net/blog/post/329288496-c%E8%AA%9E%E8%A8%80-%E9%8F%88%E7%B5%90%E4%B8%B2%E5%88%97(link-list)%E7%9A%84%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B
2.https://dotblogs.com.tw/ibllcwhchiu/2017/05/03/datastructure_part1
3.https://dotblogs.com.tw/ibllcwhchiu/2017/05/03/datastructure_part2
4.https://dotblogs.com.tw/ibllcwhchiu/2017/05/03/datastructure_part3
5.https://blog.wu-boy.com/2010/04/cc-%E5%88%87%E5%89%B2%E5%AD%97%E4%B8%B2%E5%87%BD%E6%95%B8%EF%BC%9Astrtok-network-mac-address-%E5%88%86%E5%89%B2/
6.https://brilliant.org/wiki/unrolled-linked-list/

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//K 100�� K50��
int K = 300;

struct ListNode {
    int size;
    //undefined
    char array[300];//Max_K �n�A��
    struct ListNode *next;
};

struct ListNode *head;

//Create a new node
struct ListNode *CreateNode(void)
{
    // �ŧi����ptr�A�ë��VNODE�j�p���Ŷ�
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if(newNode == NULL)
        exit(1);
    return (newNode);//�^�ǳo�ӪŶ�������
};


//insert Node
struct ListNode *InsertNode(struct ListNode *tmp){
    struct ListNode *NewNode = CreateNode();
    NewNode->next = NULL;
    //insert before the head, �z�פW�����ӵo��
    if( tmp == NULL){
        NewNode->next = head;
        head = NewNode;
    }
    else if (tmp->next == NULL){
        tmp->next = NewNode;
    }
    else{
        NewNode->next = tmp->next;
        tmp->next = NewNode;
    }
    return(head);
};

void Insert(int pos, char element){
    //index the site
    struct ListNode *tmp = head;
    int sigma_sz = head->size;
    while(sigma_sz - pos < 0 && tmp->next != NULL){
        tmp = tmp->next;
        sigma_sz += tmp->size;
    }
//    printf("count = %d\n",count);
    //int trans = sigma_sz - tmp->size
    //int place = pos - trans
    int put_place = pos - sigma_sz + tmp->size;
//    printf("pos = %d, sigma_sz = %d ,tmp->size = %d\n",pos,sigma_sz,tmp->size);
    //max size �����A�i�H�����[
    if(tmp->size < K){
        //���ᥭ��
        for(int i = tmp->size -1 ; i > put_place - 1; i--){
            tmp->array[i+1] = tmp->array[i];
            tmp->array[i] = NULL;
        }
        tmp->array[put_place] = element;
        tmp->size++;
    }
    else if (tmp->size == K ){ // tmp->size == K �w�g���F���ɭ�
        //initial
        head = InsertNode(tmp);
        struct ListNode *Next = tmp->next;
        Next->size = 0;

        for(int i = 0 ; i < K; i++){
            Next->array[i] = NULL;
        }
        //���tmp��size/////////////////////////////////////////////
        tmp->size = tmp->size / 2;

        if(put_place <= K/2){//���s�W��ƪ���m���btmp�̭�
            //���ʦ�m��next�̭�
            for (int i = 0 ; i < K/2; i++){
                Next->array[i] = tmp->array[i+K/2];
                tmp->array[i+K/2] = NULL;
                Next->size ++;
            }
            //�ťX�n�Q���J������A�᭱��ƦV�Ჾ��\n
            for (int i = tmp->size - 1; i > (put_place - 1) ; i--){
                tmp->array[i+1] = tmp->array[i];
                tmp->array[i] = NULL;
            }

            //"��J���
            tmp->array[put_place] = element;
            tmp->size++;
        }
        else{
            //���@put_place�e����
            for(int i = K/2; i < put_place; i++){
                //���L�h��M��
                Next->array[i-K/2] = tmp->array[i];
                tmp->array[i] = NULL;
            }
            //��J���
            Next->array[put_place - K/2] = element;
            //�A��put_place�᭱��
            for(int i = put_place; i < K; i++){
                //���ʹL�h��n�M��QQ
                Next->array[ i - K/2 + 1] = tmp->array[i];
                tmp->array[i] = NULL;
            }
            Next->size = K/2+1;
        }
    }
//        for(struct ListNode *ptr = head; ptr != NULL; ptr = ptr->next)
//            {
//                 for(int i = 0; i < ptr->size; i++){
//                    printf("ptr->array[%d] =  %c\n",i,ptr->array[i]);
//                }
//            }
//            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
}

void FreeNode( struct ListNode* ptr )
{
    free(ptr);
}
//delete Node
struct ListNode *DeleteNode ( struct ListNode *tmp){
    //3 situations, before head, tail, middle
    struct ListNode *help = head;
    if(tmp == head){
        head = head->next;
    }
    else{
        while ( help->next != tmp){
            help = help->next;
        }
        // delete the last
        if(tmp->next == NULL)
            help->next = NULL;
        else//delete middle
        {
            help->next = tmp->next;
//            printf("ok\n");
        }

    }
    FreeNode(tmp);
    return(head);
};

void Delete (int pos){
    //index the site
    struct ListNode *tmp = head;
    int sigma_sz = head->size;
    while(sigma_sz - pos <= 0 && tmp->next != NULL){
        tmp = tmp->next;
        sigma_sz += tmp->size;
    }
    //int trans = sigma_sz - tmp->size
    //int place = pos - trans
    int del_plc = pos - sigma_sz + tmp->size;
    tmp->array[del_plc] = NULL;
    for(int i = del_plc + 1; i < tmp->size; i++){
        tmp->array[i-1] = tmp->array[i];//���e���@��
        tmp->array[i] = NULL;
    }
    if(tmp->size > 0)
        tmp->size--;

    //�@������ 1 �ӡA�B�p��tmp->next != NULL
    while(tmp->size < K/2 && tmp->next != NULL ){
//        printf("oooooooooooooooooooooooooo\n");
        tmp->array[tmp->size] = tmp->next->array[0];
        tmp->next->array[0] = NULL;
        tmp->size ++;
        tmp->next->size --;
        for(int i = 0; i < tmp->next->size; i++){
            tmp->next->array[i] = tmp->next->array[i+1];
            tmp->next->array[i+1] = NULL;
        }
        //
        if( tmp->next->size < K/2 ){
            //�X��
            for(int i = 0; i < tmp->next->size; i++){
                tmp->array[ i + tmp->size] = tmp->next->array[i];
                tmp->next->array[i] = NULL;
                tmp->size ++;
            }
            //�R��
            head = DeleteNode(tmp->next);
        }
    }

//            for(struct ListNode *ptr = head; ptr != NULL; ptr = ptr->next)
//            {
//                 for(int i = 0; i < ptr->size; i++){
//                    printf("ptr->array[%d] =  %c\n",i,ptr->array[i]);
//                }
//            }
//            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");



}

void Display(int str, int stp){
 //index the site
    if(str == stp)
        return;
    struct ListNode *tmp = head;
    int remain = str;
    while(tmp != NULL && remain >= tmp->size){
        remain -= tmp->size;
        tmp = tmp->next;
    }
    int total_pt_num = stp - str;

    for (int i = remain; i < tmp->size; i++){
        putchar(tmp->array[i]);
        total_pt_num--;
        if(total_pt_num == 0)
            return;
    }
    int idx = 0;
    tmp = tmp->next;
    while(total_pt_num > 0)
    {
        putchar(tmp->array[idx]);
        idx++;
        total_pt_num--;
        if(idx == tmp->size)
        {
            idx = 0;
            tmp = tmp->next;
        }
    }
}

int main (){
    int read_lines,count = 0;
    int to_do; // 1, 2, 3
    int pos;
    int stp;
    char element;
    scanf("%d", &read_lines);
    //initial
    head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->size = 0;
    head->next = NULL;
    for(int i = 0 ; i < K; i++){
        head->array[i] = NULL;
    }

    while(count < read_lines){
       scanf("%d %d", &to_do, &pos);
        if(to_do == 1 ){ // to_do == 1, �[�J�F��
            scanf(" %c", &element);
            Insert(pos,element);
        }
        if (to_do == 2){
            Delete(pos);
        }
        if (to_do == 3){
            scanf("%d", &stp);
            Display(pos, stp);
            puts("");
        }
        count ++;
    }

//    printf("the finals : \n");
//            for(struct ListNode *ptr = head; ptr != NULL; ptr = ptr->next)
//            {
//                 for(int i = 0; i < ptr->size; i++){
//                    printf("ptr->array[%d] =  %c\n",i,ptr->array[i]);
//                }
//            }
//            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    return 0;
}
