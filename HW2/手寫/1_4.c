/*
算法和前一題相同。
只是這一次要多一份reverse的時間，和最後需要valid hops %2去判斷是否為奇數。
時間複雜度
做一次：
reverse = O(R-L+1) worst case = O(N)
sort = O(NlgN)
判斷是否為奇數 = O(1)
做一次總時間 = O(N)+O(NlgN)+O(1) = O(NlgN)
又因為有Q比資料因此做Q次 O(QNlgN) = O(NlgN)//Q是常數
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
    int Q;
    scanf("%d", &Q);
    int Q_data[Q][2];
    int ct = 0;
    while (ct != Q){
        //先reverse
        int left = Q_data[ct][0], right = Q_data[ct][1];
//        printf( "Q_data[%d][0] = %d,Q_data[%d][1] = %d\n ",ct,Q_data[ct][0],ct,Q_data[ct][1]);
        int chg_M_num = right - left + 1;
        for(int i = 0; i < chg_M_num; i++){
            chg_MM[i] = MM_hts[left + i];
        }
        for (int i = 0; i < chg_M_num; i++){
            MM_hts [left + i] = chg_MM [chg_M_num - i - 1];
        }
//        printf("Revs\n：");
//        for(int i = 0; i < N; i++)
//            printf("%d", MM_hts[i]);
//        printf("\n");
        mergeSort(MM_hts, 0, N-1);
        printf("total_hops = %d\n",total_hops);
        if( (valid_hops - invalid_hops) %2 != 0)
            printf("odd\n");
        else
            printf("not odd\n");

        ct++;
        invalid_hops = 0;    //歸零重算
    }

return 0;

}

