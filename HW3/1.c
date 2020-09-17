/*
Ref：https://stackoverflow.com/questions/15319561/how-to-implement-a-median-heap/15319593

*/

#include <stdio.h>
#include <stdlib.h>

int min_sz = 0;
int max_sz = 0;

//O(1)
int Median(int min_heap[], int max_heap[]) {
    if ( min_sz > max_sz){
        return min_heap[0];
    }
    else if (min_sz < max_sz){
        return max_heap[0];
    }
    else { // ==，取(n/2)th，取值小的
        if (min_heap[0] < max_heap [0]){
            return min_heap[0];
        }
        else {
            return max_heap[0];
        }
    }
}

// Insert 部分開始
void Insert_min_heap (int heap [], int value){
    heap[min_sz] = value;//置入
    min_down_to_up_heapify(heap, min_sz);
    min_sz ++;//new heap_sz
}
void min_down_to_up_heapify (int heap [],int min_sz){

    int parent = ( min_sz -1 ) /2;
    int tmp;
    if (min_sz == 0){
        return;
    }
    if ( heap[min_sz] > heap[parent]){
        return;
    }
    else{ //(heap[heap_sz] < heap [parent])
        tmp = heap[min_sz];
        heap[min_sz] = heap[parent];
        heap[parent] = tmp;
        min_down_to_up_heapify(heap, parent);
    }
}

void Insert_Max_heap (int heap [], int value){
    heap[max_sz] = value;
    max_down_to_up_heapify(heap, max_sz);
    max_sz ++;
}

void max_down_to_up_heapify (int heap [], int max_sz){
    int parent = ( max_sz -1 ) /2;
    int tmp;
    if (max_sz == 0){
        return;
    }
    if ( heap[max_sz] < heap[parent]){
        return;
    }
    else{ //(heap[heap_sz] > heap [parent])
        tmp = heap[max_sz];
        heap[max_sz] = heap[parent];
        heap[parent] = tmp;
        max_down_to_up_heapify(heap, parent);
    }
}

void Delete_min_root (int heap [], int heap_sz){
   heap[0] = heap[heap_sz];
   heap[heap_sz]= NULL;
   min_up_to_down_heapify(heap, 0, heap_sz);
}

void min_up_to_down_heapify (int heap [], int root_id ,int heap_sz){
    int min = root_id;
    int tmp;
    int l_id = root_id*2 + 1;
    int r_id = root_id*2 + 2;

    if (l_id < heap_sz && heap[l_id] < heap[min])
        min = l_id;
    if (r_id < heap_sz && heap[r_id] < heap[min])
        min = r_id;
    if (min != root_id) {
        tmp = heap[root_id];
        heap[root_id] = heap[min];
        heap[min] = tmp;
        min_up_to_down_heapify(heap, min, heap_sz);
    }
}

void Delete_max_root (int heap [], int heap_sz){
   heap[0] = heap[heap_sz];
   heap[heap_sz]= NULL;
   max_up_to_down_heapify(heap, 0, heap_sz);
}

void max_up_to_down_heapify (int heap [], int root_id ,int heap_sz){
    int max = root_id;
    int tmp;
    int l_id = root_id*2 + 1;
    int r_id = root_id*2 + 2;

    if (l_id < heap_sz && heap[l_id] > heap[max])
        max = l_id;
    if (r_id < heap_sz && heap[r_id] > heap[max])
        max = r_id;
    if (max != root_id) {
        tmp = heap[root_id];
        heap[root_id] = heap[max];
        heap[max] = tmp;
        max_up_to_down_heapify(heap, max, heap_sz);
    }
}

void Rebalance(int min_heap[], int Max_heap[], int type ){
    //type1 : min_heap 多2
    if (type == 1){
        Insert_Max_heap(Max_heap, min_heap[0]);
        min_sz --;
        Delete_min_root(min_heap, min_sz);
    }
    if (type == 2){
        Insert_min_heap(min_heap, Max_heap[0]);
        max_sz --;
        Delete_max_root(Max_heap, max_sz);
        }
}


//O(logN)
void Insert(int min_heap[], int max_heap[], int x){
    printf("into insert\n");
    int med;
    //init
    if (max_sz == 0 && min_sz == 0){
        min_heap[0] = x;
        med = x;
        min_sz ++;
    }
    else{
        med = Median(min_heap,max_heap);
        printf("Median = %d\n",med);
    }

    //不會有 == 因為都是unique
    if ( med > x ){ // 若x比較小，x 放進 max heap
        Insert_Max_heap( max_heap , x );
    }
    if (med < x){
        Insert_min_heap( min_heap, x );
    }
    int type;
    if (min_sz - max_sz > 1){
        type = 1;
        Rebalance( min_heap, max_heap,  type);
    }
    if (max_sz - min_sz > 1){
        type = 2;
        Rebalance( min_heap, max_heap,  type);
    }
}

// Insert 部分結束


//O(logN)
void Extract_Median(int min_heap[], int max_heap[], int min_sz, int max_sz) {
    //median在 min_heap中
    if (min_sz > max_sz){
        Delete_min_root(min_heap,min_sz);
    }
    //在max中
    else if( max_sz > min_sz){
        Delete_min_root(max_heap, max_sz);
    }
    else {
        //在min中
        if (min_heap[0] < max_heap [0]){
            Delete_min_root(min_heap,min_sz);
        }
        else {
            Delete_min_root(max_heap, max_sz);
        }
    }
}


int main()
{
    int tot_num,data;
    int min_heap[50];
    int max_heap[50];
    scanf("%d", &tot_num);
    printf("%d\n", tot_num);
    for (int i = 0; i < tot_num; i++){
        scanf("%d", &data);
        printf("%d\n", data);
        Insert(min_heap,max_heap,data);

        printf("no. %d times \n", i);
        printf("min_heap_sz = %d: \n", min_sz);
        for (int i = 0; i < min_sz; i++){
            printf("%d = %d\n",i,min_heap[i]);
        }
        printf("max_heap_sz = %d : \n", max_sz);
        for (int i = 0; i < max_sz; i++){
            printf("%d = %d\n",i,max_heap[i]);
        }
        printf("---------------------\n");

    }



    return 0;
}
