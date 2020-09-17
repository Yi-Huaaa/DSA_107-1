#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define prime_mod 7393933
#define prime 13
int value[];

int partition ( char spells[], int l_1,int r_1, int l_2, int r_2 ){

    printf("get in to partition \n");
    printf("l_1 = %d, r_1 = %d, l_2 = %d, r_2 = %d\n", l_1,r_1,l_2,r_2);
    int total_len = r_1 - l_1 + 1;//子字串總長度
    unsigned long long int  tmp_1, tmp_2;
    int t = 2;
    //都從1後面開始算因此l_1,l_2 != 0
    if (l_1 == r_1 && l_2 == r_2){
        if(spells[l_1] != spells[l_2]){
            printf("its 4 : spells[l_1] = %c , spells[l_2] = %c\n", spells[l_1] ,spells[l_2]) ;
            return 4;
        }
        else{
            printf("its 3 :spells[l_1] = %c , spells[l_2] = %c\n", spells[l_1] ,spells[l_2]) ;
            return 3;
        }
    }

    printf("value[%d] = %d,  value[%d] = %d\n", l_1,value[l_1], l_2,value[l_2] );
    printf("t = %d\n", t);
    printf("total_len = %d\n", total_len);
    for (int i = 0; i < total_len; i++){
         t *= prime;
//         printf("innnnnnnnnnnnnnnnnnn\n");
    }

    t = t%prime_mod;
    printf( "t = %d\n", t);
    printf("(value[l_1-1]*t) = %d, (value[l_1-1]*t)%prime_mod = %d\n ", (value[l_1-1]*t) ,(value[l_1-1]*t)%prime_mod);
    printf("(value[l_2-1]*t) = %d, (value[l_2-1]*t)%prime_mod = %d\n ", (value[l_2-1]*t) ,(value[l_2-1]*t)%prime_mod);
    tmp_1 = value[r_1] - (value[l_1-1]*t)%prime_mod;
    tmp_2 = value[r_2] - (value[l_2-1]*t)%prime_mod;

    printf("tmp_1 = %d, tmp_2 = %d\n", tmp_1,tmp_2);
    if(tmp_1 != tmp_2)
        return -1;
    else
        return 1;
}



int main(){

    int N, Q;
    scanf("%d\n", &N);
    char spells[200000];
    char tmp[200000];
    value[200000];
    int head [N];
    int len = 0;
    int now = 0;
    for (int i = 0; i < N; i++){
        head[i] = now + 1;
        fgets (tmp , 200000 , stdin);
        len = strlen(tmp);
        tmp[len-1]=NULL;
        for(int i = now; i < now+len; i++){
            spells[i] = tmp[i-now-1];
            if( i - now == 0){
                //value[i] = spells[i] ;
                value[i] = spells[i] % prime_mod;
            }
            else{
                //value[i] = abs(value[i-1] * prime + spells[i]);//倍率取
                value[i] = (value[i-1] * prime + spells[i] ) % prime_mod;//倍率取
            }
        }
        now = now+len;
    }
//    printf("len = %d, now = %d\n",len, now);
//
    for(int i = 0; i < now; i++){
        printf("spells[%d] = %c ", i, spells[i]);
        printf("value[%d] = %d ",i, value[i]);
        printf("\n");
    }
        printf("\n");
    for(int i = 0; i < N; i++)
        printf("head[i] = %d\n", head[i]);
    printf("\n");

    scanf("%d", &Q);

    int nums = 0;
    int i_1,l_1,r_1,i_2,l_2,r_2;
    while (nums != Q){
        printf("in to while \n");
        scanf("%d",&i_1);
        scanf("%d",&l_1);
        scanf("%d",&r_1);
        scanf("%d",&i_2);
        scanf("%d",&l_2);
        scanf("%d",&r_2);
        int count = r_1 - l_1 + 1;
        l_1 += head[i_1];
        r_1 += head[i_1];
        l_2 += head[i_2];
        r_2 += head[i_2];

        int get_1 = 0;
        //一開始做第一次
        printf("l_1 = %d, r_1 = %d, l_2 = %d, r_2 = %d\n", l_1, r_1, l_2,r_2);
        get_1 = partition(spells,l_1,r_1,l_2,r_2);
        printf("get_1 = %d\n", get_1);
        printf("---------------------\n");
        if(get_1 != -1){
            printf("Y\n");
            break;
        }
//////////////////////////////////////////////////////////////////////////////////////
        //跳出while 找到兩錯
        int check = 1;
        int get_ft= 0, get_bk = 0;
        int wa = 0;
        while ( get_1 != 1 && (get_ft != 1 || get_bk != 1)  ){
            printf("================\n");
            int legth = r_1 - l_1 + 1;//子字串總長度
            get_ft = partition(spells, l_1, l_1 + legth/2-1, l_2, l_2 + legth/2-1);
            get_bk = partition(spells, l_1 + legth/2, r_1, l_2 + legth/2, r_2 );

            if(get_ft == 4 && get_bk == 4){
                printf("N\n");
                break;
            }
            if( (get_ft == 4 && get_bk == 3) ||(get_ft == 3 && get_bk == 4) ){
                printf("Y\n");
                break;
            }



            //找到兩個都錯，代表有兩個錯以上
            if (get_ft == -1 && get_bk == -1){
                printf("N\n");
                check = -1;
                break;
            }
            //否則代表只有找到一個錯
            else{
                if(get_ft == -1){
                    printf("in_ft\n");
                    l_1 = l_1;
                    r_1 = l_1 + legth/2-1;
                    l_2 = l_2;
                    r_2 = l_2 + legth/2-1;
                }
                //get_bk == -1
                else{
                    printf("in_bk\n");
                    l_1 = l_1 + legth/2;
                    r_1 = r_1;
                    l_2 = l_2 + legth/2;
                    r_2 = r_2;
                }
            }
            get_ft = 0;
            get_bk = 0;
            printf("******************************8\n");
        }

        nums++;

    }

    return 0;
}
