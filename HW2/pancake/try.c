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

int num;

int query(int pancake_seq, int tea_seq){
    int p_sugar = pancake_seq;
    int t_sugar = tea_seq;
    if(p_sugar>t_sugar)
        return 1;
    if(p_sugar==t_sugar)
        return 0;
    if(p_sugar<t_sugar)
        return -1;
}
// Swapping algorithm
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *pnk,int *tea, int left, int right)
{
    int old_left = left, old_right = right;
    printf("old_left = %d, old_right = %d\n", old_left,old_right);
    int rdm_pt = rand()%(right - left + 1 ) + left;
    int p_val = pnk[rdm_pt];
    printf("random_pt = %d, p_val = %d\n",rdm_pt, p_val);
//    int pivot = left;
//    int p_val = pnk[pivot];
    int same_val ;
    printf("1__left = %d, right= %d\n",left,right);
    while (left < right)
    {
        while (query(pnk[left],p_val) != 1 && left <= right){
            if( query(pnk[left],p_val) == 0 )
                same_val = left;
            left++;
            printf("tmp_left = %d\n",left);
            if (left > old_right){
                left = old_right;
                break;
            }
        }
        printf("2__left = %d, right= %d\n",left,right);

        while (query(pnk[right],p_val) != -1 && right >= left){
            if( query(pnk[right],p_val) == 0 )
                same_val = right;
            right--;
            printf("tmp_right = %d\n",right);
            if (right < old_left){
                right = old_left;
                break;
            }
        }
        printf("3__left = %d, right= %d\n",left,right);

        if (left < right)
        {
            swap(&pnk[left], &pnk[right]);
        }
        printf("inside *********\n");
         for (int i = 0; i < num; i ++)
            printf("%d , ",pnk[i]);
        printf("\n");
        printf("---------\n");
    }
    printf("same_val = %d\n", same_val);
    printf("left = %d, right= %d\n",left,right);
    if(right == left){
        if(same_val > left)
        {
            printf("in_11");
            swap(&pnk[same_val], &pnk[right]);
            printf("\n");
            printf("tmp_1\n");
            for (int i = 0; i < num; i ++)
                printf("%d , ",pnk[i]);
            printf("\n");
            return right;
        }
        else{
            printf("in_22");
            swap(&pnk[same_val], &pnk[right]);
            printf("\n");
            printf("tmp_2\n");
            for (int i = 0; i < num; i ++)
                printf("%d , ",pnk[i]);
            printf("\n");
            return right;
        }
    }
    if(right < left){
        if(same_val >right){
            printf("in_33");
            swap(&pnk[same_val], &pnk[left]);
            printf("\n");
            printf("tmp_3\n");
            for (int i = 0; i < num; i ++)
                printf("%d , ",pnk[i]);
            printf("\n");
            return left;
        }
        else{
            swap(&pnk[same_val], &pnk[right]);
            printf("\n");
            printf("tmp_4\n");
            for (int i = 0; i < num; i ++)
                printf("%d , ",pnk[i]);
            printf("\n");
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
//    tea_sort(tea, old_left,old_right, random_pt);
//    return right;
}
void tea_sort(int *L, int left, int right, int random_pt ){
    printf("ininin\n");
    int old_left = left, old_right = right;
    int pivot = random_pt;
    int p_val = L[pivot];
    int same_val ;
    while (left < right){
        while (query(L[left],p_val) != 1 && left <= right){
            if( query(L[left],p_val) == 0 )
                same_val = left;
            left++;
            if (left > old_right){
                left = old_right;
                break;
            }
        }

        while (query(L[right],p_val) != -1 && right >= left){
            if( query(L[right],p_val) == 0 )
                same_val = right;
            right--;
            if (right < old_left){
                right = old_left;
                break;
            }
        }

        if (left < right)
        {
            swap(&L[left], &L[right]);
        }
    }
    swap(&L[same_val], &L[right]);
     printf("teateateateatea\n");
    for (int i = 0; i < num; i ++)
            printf("%d , ",L[i]);
        printf("\n");

}

void quicksort(int *pnk,int *tea, int start, int end)
{
    if (start >= end)
        return;
    int splitPoint = partition(pnk, tea, start, end);
    printf("A\n");
    printf(" start = %d , splitPoint - 1 = %d\n", start, splitPoint - 1);
    quicksort(pnk, tea, start, splitPoint - 1);
    printf("B\n");
    printf(" splitPoint + 1 = %d , end= %d\n",splitPoint + 1, end);
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

    printf("main\n");
    for (int i = 0; i < num; i ++)
            printf("%d , ",pnk[i]);
        printf("\n");


    return 0;
}
