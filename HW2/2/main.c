#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define prime_mod 1073676287
#define prime 13
typedef long long T;
T value[800000];
T h_base [800000];

int partition ( char spells[], int l_1,int r_1, int l_2, int r_2 ){
//    printf("get in to partition \n");
//    printf("str_1 : ");
//    for (int i = l_1; i < r_1 +1 ; i++)
//        printf("%c ", spells[i]);
//    printf("\n");
//    printf("str_2 : ");
//    for (int i = l_2; i < r_2 +1 ; i++)
//        printf("%c ", spells[i]);
//    printf("\n");
//
    int total_len = r_1 - l_1 + 1;//子字串總長度
    unsigned int  tmp_1, tmp_2;
    //都從1後面開始算因此l_1,l_2 != 0
    if (l_1 == r_1 && l_2 == r_2){
        if(spells[l_1] != spells[l_2]){
//            printf("its 4 : spells[l_1] = %c , spells[l_2] = %c\n", spells[l_1] ,spells[l_2]) ;
            return 4;
        }
        else{
//            printf("its 3 :spells[l_1] = %c , spells[l_2] = %c\n", spells[l_1] ,spells[l_2]) ;
            return 3;
        }
    }
//    printf("l_1 = %d, r_1 = %d, l_2 = %d, r_2 = %d\n", l_1,r_1,l_2,r_2);
//    printf("value[%d] = %d,  value[%d] = %d\n", l_1,value[l_1], l_2,value[l_2] );
//    printf("l_1 = %d, r_1 = %d, l_2 = %d, r_2 = %d\n", l_1,r_1,l_2,r_2);
//    printf("total_len = %d\n", total_len);
    tmp_1 = (value[r_1] - (value[l_1-1]*h_base[total_len])%prime_mod + prime_mod ) %prime_mod;
    tmp_2 = (value[r_2] - (value[l_2-1]*h_base[total_len])%prime_mod + prime_mod ) %prime_mod;

//    printf("tmp_1 = %d, tmp_2 = %d\n", tmp_1,tmp_2);
//    printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
    if(tmp_1 != tmp_2)
        return -1;
    else
        return 1;


}

int main(){

    int N, Q;
    scanf("%d\n", &N);
    char spells[800000];
    char tmp[800000];
//    value[200000];
//    h_base[200000];
    int head [N];
    int len = 0;
    int now = 0;
    for (int i = 0; i < N; i++){
        head[i] = now + 1;
        fgets (tmp , 200001 , stdin);
        len = strlen(tmp);
        tmp[len-1]=NULL;
        for(int i = now; i < now+len; i++){
            spells[i] = tmp[i-now-1];
            if( i - now == 0){
                //value[i] = spells[i] ;
                value[i] = spells[i] % prime_mod;
//                h_base[i] = 1;
            }
            else{
                value[i] = (value[i-1] * prime + spells[i] ) % prime_mod;
//                h_base[i] = (h_base[i -1] * prime) % prime_mod;
            }
        }
        now = now+len;
    }

    h_base[0] = 1;
    for(int i = 1; i < now; i++){
//        printf("################33\n");
        h_base[i] = ( h_base[i-1] * prime ) % prime_mod;
    }

//    printf("len = %d, now = %d\n",len, now);
//
//    for(int i = 0; i < now; i++){
//        printf("spells[%d] = %c ", i, spells[i]);
//        printf("value[%d] = %d ",i, value[i]);
//        printf("h_base[%d] = %d ",i,h_base[i]);
//        printf("\n");
//    }
//        printf("\n");
//    for(int i = 0; i < N; i++)
//        printf("head[i] = %d\n", head[i]);
//    printf("\n");

    scanf("%d", &Q);

    int nums = 0;
    int i_1,l_1,r_1,i_2,l_2,r_2;

    while (nums != Q){
//        printf("in to while \n");
        scanf("%d",&i_1);
        scanf("%d",&l_1);
        scanf("%d",&r_1);
        scanf("%d",&i_2);
        scanf("%d",&l_2);
        scanf("%d",&r_2);
        l_1 += head[i_1];
        r_1 += head[i_1];
        l_2 += head[i_2];
        r_2 += head[i_2];

        int get_1 = 0;
        //一開始做第一次
//        printf("l_1 = %d, r_1 = %d, l_2 = %d, r_2 = %d\n", l_1, r_1, l_2,r_2);
        get_1 = partition(spells,l_1,r_1,l_2,r_2);
//        printf("get_1 = %d\n", get_1);
//        printf("---------------------\n");
        //0. 全對
        if( get_1 == 1 || get_1 == 3 || get_1 == 4 ){
//            printf("ininin\n");
            printf("Y\n");
        }

        //跳出while 找到兩錯
        int get_ft= 0, get_bk = 0;
        while ( get_1 == -1 && (get_ft != 1 || get_bk != 1)  ){
            get_ft= 0;
            get_bk = 0;
//            printf("================\n");
            int legth = r_1 - l_1 + 1;//子字串總長度
            get_ft = partition(spells, l_1, l_1 + legth/2-1, l_2, l_2 + legth/2-1);
            get_bk = partition(spells, l_1 + legth/2, r_1, l_2 + legth/2, r_2 );
//            printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQq\n");
//            printf("get_ft = %d, get_bk = %d\n", get_ft, get_bk);

            // 1. 兩個單字，兩個都錯
            if(get_ft == 4 && get_bk == 4){
                printf("N\n");
                break;
            }
//            printf("OOOOOOOOOOOOOOOOOOOOOOOO\n");
            // 2.一格單字，一個對一個錯
            if( (get_ft == 4 && get_bk == 3) || (get_ft == 3 && get_bk == 4)){
                printf("Y\n");
                break;
            }
//            printf("PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n");
            // 3.一個單字對，一段錯   就繼續切後面
            if( ( get_ft == 3 && get_bk == -1 ) || ( get_ft == -1 && get_bk == 3 ) ){
//                printf("IN____1\n");
                 if(get_ft == -1){
//                        printf("in_ft\n");
                        l_1 = l_1;
                        r_1 = l_1 + legth/2-1;
                        l_2 = l_2;
                        r_2 = l_2 + legth/2-1;
                    }
                    //get_bk == -1
                    if(get_bk == -1){
//                        printf("in_bk\n");
                        l_1 = l_1 + legth/2;
                        r_1 = r_1;
                        l_2 = l_2 + legth/2;
                        r_2 = r_2;
                    }
            }
//            printf("RRRRRRRRRRRRRRRRR\n");
            //4.5. 一格單字錯，一段錯   代表兩個都有錯
            if( (get_ft == 4 && get_bk == -1 ) || (get_ft == -1 && get_bk == 4) || (get_ft == -1 && get_bk == -1) ){
                printf("N\n");
                break;
            }
            //找到兩個大段都錯，代表有兩個錯以上
            if (get_ft == -1 && get_bk == -1){
                printf("N\n");
                break;
            }
            //6.一個單字錯，後面一段對(後面一段一定只是兩個字最多)
            if( ( get_ft == 4 && get_bk == 1 ) || (get_ft == 1 && get_bk == 4)){
//                printf("IN______2\n");
                printf("Y\n");
                break;
            }

            //7.一段對，一段錯
            if( (get_ft == 1 && get_bk == -1) || (get_ft == -1 && get_bk == 1)){
//                printf("IN____3\n");
//                printf("in___\n");
                if(get_ft == -1){
//                        printf("in_ft\n");
                        l_1 = l_1;
                        r_1 = l_1 + legth/2-1;
                        l_2 = l_2;
                        r_2 = l_2 + legth/2-1;
                    }
                    //get_bk == -1
                    if(get_bk == -1){
//                        printf("in_bk\n");
                        l_1 = l_1 + legth/2;
                        r_1 = r_1;
                        l_2 = l_2 + legth/2;
                        r_2 = r_2;
                    }
            }
//
//            if( (get_ft == 1 && get_bk == 1 ) || (get_ft ==  3 && get_bk == 1 ) ||
//                 (get_ft == 1 && get_bk == 3 ) || (get_ft == 3 && get_bk == 3 ) )
//            {
//                printf("Y\n");
//                break;
//            }
//            printf("******************************8\n");
        }

        nums++;
//        printf("nums = %d\n", nums);

    }

    return 0;
}
