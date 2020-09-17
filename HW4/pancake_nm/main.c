#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pancake_names.h"

/*
不用讀檔
a. 總共有 N 個名字存在 char S array中。
b. 總共有 M 個問題存在 Q1 array 和 Q2 array 中。
*/



//475255
int hash_table[35353550];// 最大的hash : zzzz : 475254
int acc[35353550];// 475254 : zzzz 的 hash，又 a自1開始記錄，因此array開到 475255


int ch_hash(char c)
{
//只有小寫字母
    return (c - 'a') + 1;
}
//int nm_hash(char *s ){
//    int t = strlen(s);
//    int ret = 0;
//    for (int i = 0; i < t; i++){
//        ret = ret*26 + ch_hash( s[i] );
//    }
//    return ret;
//}

int nm_hash(char *s){
    int t = strlen(s);
    if (t == 1){
//        printf("in_1\n");
        return ch_hash(s[0]) * 1000000;
    }
    if (t == 2){
//        printf("in_2\n");
        return ch_hash(s[0]) * 1000000 + ch_hash(s[1])*10000 ;
    }
    if (t == 3){
//        printf("in_3\n");
        return ch_hash(s[0]) * 1000000 + ch_hash(s[1])*10000 + ch_hash(s[2])* 100;
    }
    if (t == 4){
//        printf("in_4\n");
        return ch_hash(s[0]) * 1000000 + ch_hash(s[1])*10000 + ch_hash(s[2])* 100 + ch_hash(s[3]);
    }

}

void count_num ( int nm_hsh[], int N, int hash_tbl[]){
    //init
    for (int i = 0; i < 35353551; i++)
        hash_tbl[i] = 0;
    //統計
    for (int i = 0; i < N; i++){
        hash_tbl[ nm_hsh[i] ] ++;
    }
}

void accumulate ( int hash_table[], int acc[]){
    acc[0] = 0;
    for (int i = 1; i < 35353551; i ++){
        acc[i] = acc[i-1] + hash_table[i];
    }
}


int main() {

    InitPancakes();
    int tmp = 0;
    int nm_hh[N];
    //int acc
//    char S[12][5] = {"a", "so", "aa", "cout", "aaa", "bbf", "bbf", "zzzz", "a", "a",  "haha", "soya"};
//    char Q1[6][5] = {"a","a", "haha", "bbf", "bbf"};
//    char Q2[6][5] = {"a","aa", "soya", "so", "cout"};
//    ///讀進名字 char S，算完 hash
    while (tmp < N){
        nm_hh[tmp] = nm_hash( S[tmp]);
        tmp++;
    }
    ///counting sort
//    for (int i = 0 ; i < N; i++){
//        printf("nm_hh[%d] = %d\n ",i, nm_hh[i]);
//    }

//    printf("here-1\n");
    count_num(nm_hh, N, hash_table);
//    printf("here-3\n");
    accumulate(hash_table, acc);
//    printf("here-3\n");
//    for (int i = 0; i < 35353550; i++){
//        if (hash_table[i] != 0){
//            printf("hash_table[%d] = %d\n", i, hash_table[i]);
//        }
//    }
//
//    for (int i = 1; i < 35353551; i++){
//        if (acc[i] != acc[i-1]){
//            printf("acc[%d] = %d\n", i, acc[i]);
//        }
//    }


    tmp = 0;
    int Q1_hh, Q2_hh;

    while (tmp < M){
        Q1_hh = nm_hash(Q1[tmp]);
        Q2_hh = nm_hash(Q2[tmp]);
        AnswerArvin(tmp, acc[Q2_hh] - acc[Q1_hh] + hash_table[Q1_hh]);
//        printf("ans = %d\n", cnt);
        tmp++;
    }

ByeArvin();


//InitPancakes();

//    while (M--){
//
//        AnswerArvin(i, cnt);
//        i++;
//    }
//
//    for (int i = 0; i < M; ++i) {
//        int cnt = 0;
//        for (int j = 0; j < N; ++j) {
//            if (strcmp(S[j], Q1[i]) >= 0 && strcmp(S[j], Q2[i]) <= 0)
//            ++cnt;
//        }
//
//    //此處要修改
//    AnswerArvin(i, cnt);
//    }
    //不動
//    ByeArvin();
    return 0;
}
