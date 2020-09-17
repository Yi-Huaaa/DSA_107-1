#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N,Q;


int main()
{
    scanf("%d\n", &N);
    char spells[N][200000];
    for (int i = 0; i < N; i++)
    {
        fgets (spells[i] , 200000 , stdin);
//        for (int j = 0; j < strlen(spells[i]); j++){
//            printf("%c",spells[i][j]);
//        }
//        printf("\n");
    }

//    for(int i = 0; i < N; i++){
//        for (int j = 0; j < 4; j++){
//            printf("%c",spells[i][j]);
//        }
//        printf("\n");
//    }
//
    scanf("%d", &Q);
    int queries[Q][6];
    for (int i = 0; i < Q; i++)
        for (int j = 0; j < 6; j++)
            scanf("%d",&queries[i][j]);

//    for(int i = 0; i < Q; i++){
//        for (int j = 0; j < 6; j++){
//            printf("%d",queries[i][j]);
//        }
//        printf("\n");
//    }
//    printf("------------\n");

    int nums = 0;
    while (nums != Q){
        int i_1 = queries[nums][0];//ĴX
        int l_1 = queries[nums][1];//Y
        int r_1 = queries[nums][2];//
        int i_2 = queries[nums][3];
        int l_2 = queries[nums][4];
        int r_2 = queries[nums][5];


        int count = r_1 - l_1 + 1;
//        printf("line_1\n");
//        for (int i = 0; i < count; i++)
//            printf("%c ", spells[i_1][l_1 + i] );
//        printf("\n");
//        printf("line_2\n");
//        for (int i = 0; i < count; i++)
//            printf("%c ", spells[i_2][l_2 + i] );
//        printf("\n");
//        printf("--------------\n");

        int wrong = 0;
        int a = 0;
        for (int i = 0; i < count; i++){
            if(spells[i_1][l_1 + i] != spells[i_2][l_2 + i])
                wrong++;
            if(wrong > 1)
                break;
                a++;
        }
        if( a == count)
            printf("Y\n");
        else
            printf("N\n");

        nums++;
    }





    return 0;
}
