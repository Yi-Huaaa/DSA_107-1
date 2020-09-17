/*
因為題目要求須要在nlgn的時間內做完，因此選擇merge sort做為sort的方式。
想法：
在做merge sort的時候計算，對於每一個數值而言，有多少個值比他大的數值，從其左邊在sort的過程中被移到 (因為本數值較大，故被往後移動) 這個數字的右邊。
舉例來說，假設一個seq 原本的長像是：3,8,1,6,10。
經過sort後長得像：1,3,6,8,10，就可以知道對於數值1而言，他最多可以有4個(因為在他後面有4個數字比他大)合法的hops。
然而比對原本的seq，會發現到在1前面有兩個數值比1的數字。因此對於1而言它真正的合法hops只有ˋ4-2 = 2 ，也就是最多只有兩個合法hops。
因此，為了獲得這個[ 有多少比他大的數字原本排在他前面 ] 這個值。可以先開一個用來計數數值的int invalid_hops = 0，在做merge sort的時候就可以每做一次交換，
-
就對 invalid_hops 的值進行的 +x (因為一定對於一個比較小的數值來說，他減少了一個合法的hops)。換言之就是在一次交換，有一個比他大的數字被往後移動了，因此合法的hops數要-1。
因此在做完整個merge sort之後，就可以獲得所有不合法的hops數 =  invalid_hops。
又任取兩數必有一數值另一個小(因為題目說每座山的山高都是unique的)，因此合法的hops 數 = C(所有山的數量)取2 -  invalid_hops，即為所求。
花費時間：
在做merge sort的時候會花O(NlgN)，而做紀錄是O(1)，
又最後計算 valid_hops 是一條家法算式也是O(1)，
因此總花費時間是 = O(NlgN) + O(1) + O(1) = O(NlgN)。

*/
#include <stdlib.h>
#include <stdio.h>
#include  <limits.h>

int invalid_hops = 0;

void merge(int arr[], int l, int m, int r)
{
//    printf("in\n");
//    printf("l = %d, m = %d, r = %d\n",l,m,r );
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    int con_in_right = 0;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            con_in_right = 0;
//            printf("in left \n");
//            printf("arr[%d] = %d, L[%d] = %d\n",k,arr[k],i ,L[i]);
            arr[k] = L[i];
//            printf("l+i-k  = %d\n",l+i-k );
//            invalid_hops += ( l+i-k );
            i++;
        }
        else
        {
//            printf("con_in_right = %d\n",con_in_right);
//            printf("in right \n");
//            printf("arr[%d] = %d, R[%d] = %d\n",k,arr[k], j,R[j]);
            arr[k] = R[j];
//            printf("k-i+n1+j -k - con_in_right = %d\n",k-i+n1+j -k - con_in_right);
            invalid_hops += ( k-i+n1+j -k - con_in_right);
            j++;
            con_in_right ++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
//        printf("arr[l] =%d, arr[m] = %d\n",arr[l],arr[m]);
        mergeSort(arr, l, m);
//        printf("arr[m+1] =%d, arr[r] = %d\n",arr[m+1],arr[r]);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}


int main(){
    //先讀進來山的總數，和山高array，且第一座山為0
    //下面假設N = 12, 且山高如下
    int N ;
    scanf("%d", &N);
    int MM_hts[N];
    //最多的時候是C N 取 2
    int valid_hops = (N * (N-1))/2;

    for (int i = 0; i < N; i++){
        scanf("%d", &MM_hts[i] );
    }
    mergeSort(MM_hts, 0, N-1);

    printf("total_valid__hops = %d\n",valid_hops - invalid_hops);

return 0;

}

