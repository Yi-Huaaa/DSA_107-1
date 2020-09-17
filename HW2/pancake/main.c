/*
Ref:
1.https://stackoverflow.com/questions/39950926/quick-sort-implementation-in-c
2.https://www.geeksforgeeks.org/quick-sort/
//#include Arvin.h
int query(int pancake_seq, int tea_seq){
    //return 1 if sugar in pancake > sugar in tea
    //return 0 if sugar in pancake == sugar in tea
    //return -1 if sugar in pancake < sugar in tea
}
*/
/*
1.要交替做 pancake tea
2.做 random pivot
*/
#include <stdio.h>
#include <stdlib.h>
#include <Arvin.h>
int num;
//
//int query(int pancake_seq, int tea_seq){
//    int p_sugar = pancake_seq;
//    int t_sugar = tea_seq;
//    if(p_sugar>t_sugar)
//        return 1;
//    if(p_sugar==t_sugar)
//        return 0;
//    if(p_sugar<t_sugar)
//        return -1;
//}
//int query(int pancake_seq, int tea_seq){
//    int p_sugar = pancake_seq;
//    int t_sugar = tea_seq+1;
//    if(p_sugar>t_sugar) return 1;
//    if(p_sugar==t_sugar) return 0;
//    if(p_sugar<t_sugar) return -1;
//}
// Swapping algorithm
void swap(int *a, int *b)
{
    //only exchange pointer 
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *pnk,int *tea, int left, int right)
{
    int old_left = left, old_right = right;
//    printf("old_left = %d, old_right = %d\n", old_left,old_right);
    int rdm_pt = rand()%(right - left + 1 ) + left;
    int p_val = tea[rdm_pt];
//    printf("random_pt = %d, p_val = %d\n",rdm_pt, p_val);
//    int pivot = left;
//    int p_val = pnk[pivot];
    int same_val ;
//    printf("1__left = %d, right= %d\n",left,right);
    while (left < right)
    {
        while (query(pnk[left],p_val) != 1 && left <= right){
            if( query(pnk[left],p_val) == 0 )
                same_val = left;
            left++;
//            printf("tmp_left = %d\n",left);
            if (left > old_right){
                left = old_right;
                break;
            }
        }
//        printf("2__left = %d, right= %d\n",left,right);

        while (query(pnk[right],p_val) != -1 && right >= left){
            if( query(pnk[right],p_val) == 0 )
                same_val = right;
            right--;
//            printf("tmp_right = %d\n",right);
            if (right < old_left){
                right = old_left;
                break;
            }
        }
//        printf("3__left = %d, right= %d\n",left,right);

        if (left < right)
        {
            swap(&pnk[left], &pnk[right]);
        }
//        printf("inside *********\n");
//         for (int i = 0; i < num; i ++)
//            printf("%d , ",pnk[i]);
//        printf("\n");
//        printf("---------\n");
    }
//    printf("same_val = %d\n", same_val);
//    printf("left = %d, right= %d\n",left,right);
    if(right == left){
        if(same_val > left)
        {
//            printf("in_11");
            swap(&pnk[same_val], &pnk[right]);
//            printf("\n");
//            printf("tmp_1\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",pnk[i]);
//            printf("\n");
            tea_sort(tea, pnk, old_left,old_right, right);
            return right;
        }
        else{
//            printf("in_22");
            swap(&pnk[same_val], &pnk[right]);
//            printf("\n");
//            printf("tmp_2\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",pnk[i]);
//            printf("\n");
            tea_sort(tea,pnk, old_left,old_right, right);
            return right;
        }
    }
    if(right < left){
        if(same_val >right){
//            printf("in_33");
            swap(&pnk[same_val], &pnk[left]);
//            printf("\n");
//            printf("tmp_3\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",pnk[i]);
//            printf("\n");
            tea_sort(tea,pnk, old_left,old_right, left);
            return left;
        }
        else{
            swap(&pnk[same_val], &pnk[right]);
//            printf("\n");
//            printf("tmp_4\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",pnk[i]);
//            printf("\n");
            tea_sort(tea,pnk, old_left,old_right, right);
            return right;
        }
    }


//    swap(&pnk[same_val], &pnk[right]);
//    printf("\n");
//
//    printf("tmp\n");
//    for (int i = 0; i < num; i ++)
//            printf("%d , ",pnk[i]);
//        printf("\n");
//    return right;
}
void tea_sort(int *tea,int *pnk, int left, int right, int rdm_pt ){
//    printf("in_tea_st\n");
    int old_left = left, old_right = right;
    int p_val = pnk[rdm_pt];
//    printf("random_pt = %d, p_val = %d\n",rdm_pt, p_val);
    int same_val ;
//    printf("1__left = %d, right= %d\n",left,right);
//    printf("ar first\n");
//     for (int i = 0; i < num; i ++)
//            printf("%d , ",tea[i]);
//        printf("\n");
//        printf("---------\n");
    while (left < right)
    {
        while (query(p_val,tea[left]) != -1 && left <= right){
            if( query(p_val,tea[left]) == 0 )
                same_val = left;
            left++;
//            printf("tmp_left = %d\n",left);
            if (left > old_right){
                left = old_right;
                break;
            }
        }
//        printf("2__left = %d, right= %d\n",left,right);

        while (query(p_val,tea[right]) != 1 && right >= left){
            if( query(p_val,tea[right]) == 0 )
                same_val = right;
            right--;
//            printf("tmp_right = %d\n",right);
            if (right < old_left){
                right = old_left;
                break;
            }
        }
//        printf("3__left = %d, right= %d\n",left,right);

        if (left < right)
        {
            swap(&tea[left], &tea[right]);
        }
//        printf("inside *********\n");
//         for (int i = 0; i < num; i ++)
//            printf("%d , ",tea[i]);
//        printf("\n");
//        printf("---------\n");
    }
//    printf("same_val = %d\n", same_val);
//    printf("left = %d, right= %d\n",left,right);
    if(right == left){
        if(same_val > left)
        {
//            printf("in_11");
            swap(&tea[same_val], &tea[right]);
//            printf("------------\n");
//            printf("tea_tmp_1\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",tea[i]);
//            printf("\n----------\n");
        }
        else{
//            printf("in_22");
            swap(&tea[same_val], &tea[right]);
//            printf("------------\n");
//            printf("tea_tmp_2\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",tea[i]);
//            printf("\n-------------\n");
        }
    }
    if(right < left){
        if(same_val >right){
//            printf("in_33");
            swap(&tea[same_val], &tea[left]);
//            printf("-----------------\n");
//            printf("tea_tmp_3\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",tea[i]);
//            printf("\n-------------------\n");
        }
        else{
            swap(&tea[same_val], &tea[right]);
//            printf("--------------\n");
//            printf("tea_tmp_4\n");
//            for (int i = 0; i < num; i ++)
//                printf("%d , ",tea[i]);
//            printf("\n---------------\n");
        }
    }
}

void quicksort(int *pnk,int *tea, int start, int end)
{
    if (start >= end)
        return;
    int splitPoint = partition(pnk, tea, start, end);
//    printf("A\n");
//    printf(" start = %d , splitPoint - 1 = %d\n", start, splitPoint - 1);
    quicksort(pnk, tea, start, splitPoint - 1);
//    printf("B\n");
//    printf(" splitPoint + 1 = %d , end= %d\n",splitPoint + 1, end);
    quicksort(pnk, tea, splitPoint + 1, end);
}


int main()
{
    int a = 0;
    scanf("%d", &num);
    int pnk[num];
    int tea[num];
    while(a != num){
        scanf("%d", &pnk[a]);
        a++;
    }
    a = 0;
    while(a != num){
        scanf("%d", &tea[a]);
        a++;
    }

    quicksort(pnk,tea, 0, num-1);

    for(int i = 0; i < num; i ++){
        printf("%d %d\n", pnk[i],tea[i]);
    }

//    printf("main_pan\n");
//    for (int i = 0; i < num; i ++)
//            printf("%d , ",pnk[i]);
//        printf("\n");
//    printf("main_tea\n");
//    for (int i = 0; i < num; i ++)
//            printf("%d , ",tea[i]);
//        printf("\n");

    return 0;
}
