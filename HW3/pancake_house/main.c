#include <stdlib.h>
#include <stdio.h>
#define ULL unsigned long long int
//
void Insert (int heap [], int value, int heap_sz){
    // put_place = heap _sz on array
    heap[heap_sz] = value;
    down_to_up_heapify(heap, heap_sz);
}

//由下至上
void down_to_up_heapify (int heap [], int heap_sz){
    int parent = ( heap_sz -1 ) /2; // 3,4 的 parent 是 1
    int tmp;
    if (heap_sz == 0){
        return;
    }
    if ( heap[heap_sz] >= heap[parent]){
        return;
    }
    else{ //(heap[heap_sz] < heap [parent])
        tmp = heap[heap_sz];
        heap[heap_sz] = heap[parent];
        heap[parent] = tmp;
        down_to_up_heapify(heap, parent);
    }
}

//
int Delete_root (int heap [], int heap_sz){
   int min = heap[0];
   heap[0] = heap[heap_sz];
   heap[heap_sz]= NULL;

   up_to_down_heapify(heap, 0, heap_sz);
   return min;
}

void up_to_down_heapify (int heap [], int root_id ,int heap_sz){
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
        up_to_down_heapify(heap, min, heap_sz);
    }
}



int main(){
//    printf("hehe\n");
    int tot_pk;// total pancake has made
    scanf("%d", &tot_pk);
    int heap [500000];// array 做 heap
    int inst,data;
    int heap_sz = 0;
//    printf("%d", tot_pk);
    ULL ans = 0;

    for (int i = 0; i < tot_pk; i++){
        scanf("%d",&inst);// instruction
//        printf("inst = %d\n", inst);
        if (inst == 0){ // instruction == 0, push in
            scanf("%d", &data);
            ans += data;
            Insert(heap, data, heap_sz);
            heap_sz++;
        }
        else { // instruction == 1, pop out
            heap_sz--;
            ans -= Delete_root(heap,heap_sz);

        }
    }


//    for (int i = 0; i < heap_sz; i ++){
//        printf("%d = %d\n", i, heap[i]);
//    }
    printf("%llu\n", ans);



    return 0;
}
