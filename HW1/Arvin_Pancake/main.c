#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
struct Stack{
    int top;
    int Max_sz;
    int* data;
};
struct Stack *create_stack( int size ){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->Max_sz = size -1;
    stack->top = -1;
    stack->data = (int*) malloc(stack->Max_sz * sizeof(int));
    return stack;
};
bool isFull( struct Stack *stack ){
    return stack->top == stack->Max_sz-1;
}


// Stack is empty when top is equal to -1
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int num){
    if( isFull(stack) == true){
        printf("%s is bomb\n", stack);
        return;
    }
    else
        stack->data[++stack->top] = num;
}
// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack){
    if ( isEmpty(stack) == true){
        printf("QQ");
        return -1;
        //since there can't be no  return
    }
    else
        return (stack->data[stack->top--]);
}

int peek(struct Stack *stack) {
    return stack->data[stack->top];
}

int main()
{
    int pancake, eat;
    scanf("%d %d", &pancake, &eat);
    int tmp_pancake[pancake] ;
    int cut = 0;
    char string [pancake *2 -1];
    struct Stack *tmp = create_stack(2*pancake);
    struct Stack *Max = create_stack(2*pancake);
    bool haha = false;
    int Max_stk_sz = 0;
    //  read in and find the max

    while( scanf("%s", string) != EOF){
        tmp_pancake[cut] = atoi(string);
        //printf("tmp_array = %d\n",tmp_pancake[cut]);
        if (cut == 0){
            push(Max,tmp_pancake[cut]);
            Max_stk_sz ++;
        }
        else{//cut != 0
        //
            if( tmp_pancake[cut] <= peek(Max)){

                push( Max, tmp_pancake[cut] );
                Max_stk_sz++;
            }
            while ( tmp_pancake[cut] > peek(Max) && isEmpty(Max) == false){
                pop(Max);
                haha = true;
                Max_stk_sz--;
            }
            if(haha == true){
                push(Max,tmp_pancake[cut]);
                Max_stk_sz++;
                haha = false;
            }
        }
        cut ++;
        if(cut == pancake){
            break;
        }
    }

//    printf("print out the tmp_pancake array\n");
//    for (int i = 0; i < pancake; i++){
//        printf("tmp_pancake[%d] = %d \n", i, tmp_pancake[i]);
//    }
//
//    printf("Max_stk_sz =  %d\n", Max_stk_sz);

//    //檢查peek會不會吃東西，不會
//    for (int i = 0 ; i < 5; i++){
//        printf("peek 第 %d 次 = %d\n", i , peek(Max));
//    }
//    //檢查peek會不會吃東西，不會


//    for (int i = 0; i < Max_stk_sz; i++){
//        printf("Max_stack : ");
//        printf("%d\n",pop(Max));
//    }
    //Max finding OK

// 將Max倒轉成 Max_reverse
   struct Stack *Max_reverse = create_stack(2*pancake);
    for (int i =0; i < Max_stk_sz; i++){
        int tmp_trans = 0;
        tmp_trans = pop(Max);
        push(Max_reverse,tmp_trans);
    }
//  檢查 Max_reverse是否正確
//    for (int i = 0; i < Max_stk_sz ; i++){
//        printf("Max_reverse : ");
//        printf("%d\n",pop(Max_reverse));
//    }

// 將Max倒轉成 Max_reverse



    int pan_slp = 0;//
    //push into tmp stack
    //initialize
    while(tmp_pancake[pan_slp] != peek(Max_reverse) ){
        //printf("in the first while\n");
        push(tmp,tmp_pancake[pan_slp]);
        //printf("peek(tmp) = %d\n",peek(tmp));
        pan_slp ++;
    }
    printf("%d ", pop(Max_reverse));
    cut --;
    Max_stk_sz = Max_stk_sz -1;
    pan_slp++;
    //printf("pan_slp = %d\n", pan_slp);

    while (Max_stk_sz > 0){
        if ( peek(tmp) < peek(Max_reverse) || isEmpty(tmp) ){
            while ( tmp_pancake[pan_slp] != peek(Max_reverse) ){
                push(tmp,tmp_pancake[pan_slp]);
                pan_slp++;
            }
            //printf("peek(tmp) = %d",peek(tmp));
            printf("%d ", pop(Max_reverse));
            cut--;
            Max_stk_sz--; // since pop out another large one
            pan_slp ++;
        }
        else if ( peek(tmp) >= peek(Max_reverse) ){
            printf("%d ", pop(tmp));
            cut--;
        }
    }

    for (int i = 0; i < cut; i++){
        printf("%d ", pop(tmp));
    }


    return 0;
}
