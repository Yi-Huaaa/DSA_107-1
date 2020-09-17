#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef long long T;
#define prime_mod 1073676287
T prime=13;
int gp_num = 0;
T hash_table[3][50000007]; // 0:id，1:nm_hash, 2:ing_hash
struct GP {
    struct GP *parent;
    char *name;
    int gp_id;
};

struct GP* gp_array[2][50000007]; //id, node

struct GP* create_GP(void){
    struct GP *gp = (struct GP*)malloc(sizeof(struct GP));
    if(gp == NULL)
        exit(1);
    return (gp);
};


//name hash okok
T name_hash( char*s ){
    int len = strlen(s);
    T h = 0;
    for (int i = 0; i <len; i++ ){
        h = ((h*prime)%prime_mod + s[i])%prime_mod;
    }
    return h;
}

//Apple return 2^(Apple)%prime_mod
T ingd_hash ( char *s ){
//    printf("in to the ing_hash.\n");
    T ing = 0;
    ing = name_hash(s);
//    printf("ing for nm_hash = %lld\n", ing);
    T ret = 1;
    for (int i = 0; i < ing; i++){
        ret = (ret*7)%prime_mod;
    }
//    printf("%lld\n", ret);
    return ret;
}

void New (char *name, T nm_hash, T ing_hash){
    struct GP *newgp = create_GP();
    newgp->name = *name;
    newgp->parent = NULL;
    newgp->gp_id = gp_num;
    gp_array[0][gp_num] = gp_num; //id
    gp_array[1][gp_num] = newgp; //node
    for (int i = 0; i < gp_num; i++){
        printf("QQQQQQQq\n");
        if (hash_table[2][i] == ing_hash){
            printf("yoyo\n");
            Merge(hash_table[2][i],nm_hash,0);
        }
    }
    gp_num ++;

}

void Merge (T tmp_name1_hash, T tmp_name2_hash, int type){
//    printf("get in to merge\n");
    int i1 = 0, i2 = 0;
    //tmp_name在gp_array中的哪個位置求得id
    while( tmp_name1_hash != hash_table[1][i1]){
        i1++; // 取位置
    }
    while( tmp_name2_hash != hash_table[1][i2]){
        i2++;
    }
    int id1 = hash_table[0][i1];//取值
    int id2 = hash_table[0][i2];
//    printf("__1\n");
//    printf("i1 = %d, i2 = %d, id1 = %d, id2 = %d\n", i1, i2, id1, id2);
    //swap
    int tmp_id, tmp_i;
    if ( id2 < id1){
        tmp_id = id2;
        id2 = id1;
        id1 = tmp_id;
        tmp_i = i2;
        i2 = i1;
        i1 = tmp_i;
    }
//    printf("__2\n");
//    printf("i1 = %d, i2 = %d, id1 = %d, id2 = %d\n", i1, i2, id1, id2);
    struct GP* tmp1 = gp_array[1][id1]; //node
    struct GP* tmp2 = gp_array[1][id2];
    if (type == 0){
        printf("%s %s\n", tmp1->name, tmp2->name );
    }

    while (tmp1->parent != NULL)
        tmp1 = tmp1->parent;
    tmp2->parent = tmp1;
    //food_hash change
    T new_ing_hash= hash_table[2][i1] + hash_table[2][i2];
    hash_table[2][i1] = new_ing_hash;
    hash_table[2][i2] = new_ing_hash;
    //gp_id  change
    tmp2->gp_id = tmp1->gp_id;
//    printf("tmp2->gp_id = %d, tmp1->gp_id = %d\n",tmp2->gp_id , tmp1->gp_id);
    hash_table[0][i2] = id1; //對
//    printf("hash_table : \n");
//    for (int i = 0; i < gp_num; i++){
//        printf("id  =  %d\n", hash_table[0][i]);
//        printf("nm_hash = %lld\n",hash_table[1][i]);
//        printf("ing_hash = %lld\n",hash_table[2][i] );
//        printf("\n");
//    }
//    printf("\n");
    gp_array[0][id2] = id1; // 對
//    printf("gp_array\n");

}





int main (){
    int N;
    scanf("%d", &N);
//    printf("%d\n", N);
    char inst[10];//read instruction
    char name1 [120];//New's name
    char name2 [120];// use on merge
    char tmp_fd[120];
    int ingdt;// 2 AB's 2,ingredient
    T tmp_name1_hash, tmp_name2_hash;
    int a = N;
    int type = 1;
    while ( a > 0 ){
        T tmp_ingd_hash = 0;
        scanf("%s", inst);
        if (inst[0] == 'N'){ // inst == New
            scanf("%s%d", name1, &ingdt);
//            printf("\n");
            tmp_name1_hash = name_hash(name1);
//            printf("%lld\n", tmp_name1_hash);
            for (int i = 0; i < ingdt; i++){
                scanf("%s", tmp_fd);
                tmp_ingd_hash += ingd_hash(tmp_fd);
            }
            printf("See : %lld\n", tmp_ingd_hash);
            hash_table[0][gp_num] = gp_num;//存id
            hash_table[1][gp_num] = tmp_name1_hash;//名字的hash table
            hash_table[2][gp_num] = tmp_ingd_hash;//名字的hash table
            printf("hash_table : \n");
            printf("hash_table[0][%d] = %lld, hash_table[1][%d] = %lld,hash_table[2][%d] = %lld",
                       gp_num,hash_table[0][gp_num],gp_num,hash_table[1][gp_num],gp_num,hash_table[2][gp_num]);
            printf("\n");
            New(name1, tmp_name1_hash, tmp_ingd_hash);// New 結束
        }
        else { //instruction = merge
            scanf("%s", name1);
            scanf("%s", name2);
            tmp_name1_hash = name_hash(name1);
            tmp_name2_hash = name_hash(name2);
//            printf("tmp_name1_hash = %lld, tmp_name2_hash = %lld\n", tmp_name1_hash,tmp_name2_hash);
            //開始找group
            Merge( tmp_name1_hash, tmp_name2_hash, type);
        }

    a--;
    }

    return 0;
}
