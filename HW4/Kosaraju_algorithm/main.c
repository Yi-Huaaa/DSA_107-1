/*
Ref :
1. http://www.csie.ntnu.edu.tw/~u91029/Component.html
2. https://www.geeksforgeeks.org/graph-and-its-representations/
3. stack的 structure用這邊的 : https://www.geeksforgeeks.org/stack-data-structure/ (怕code太冗長，因此直接叫)

時間複雜度：時間複雜度為兩次 DFS 的時間，以及顛倒所有邊的時間。
資料結構是 adjacency lists ，需要顛倒所有邊，總時間複雜度 O(V+E) 。
下面利用array代表stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
//for DFS


struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};

struct Graph* graph ;
struct Graph* rev_gph;

struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*) malloc( V * sizeof(struct AdjList));
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

//src : source, dest :destination
void addEdge(struct Graph* graph, int src, int dest)
{
    //無向圖，加上兩邊
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

///////////////////

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

struct stack* stk;
void push_in_stk ( int i) {
    push(stk, i);
}

void DFS (int i, int V, bool visited[]){
    printf("inside, visiting : %d\n", i);
    struct AdjListNode* tmp = graph->array[i].head; //point at the first number
    while (tmp != NULL && visited[i] == false){
        visited[i] = true;
        for (int j = 0; j < V; j++){
            printf("visited[%d] = %d\n", j , visited[j]);
        }
        printf("\n");
        DFS( tmp->dest, V, visited);
        tmp = tmp->next;
        //加入stack 中
        ///
        if (isFull(stk) == false)
            push_in_stk(i);
        printf("stack now is : %d\n", peek(stk));
        ///

    }
    if (tmp != NULL && visited[i] == true){
        printf("already visited %d .\n", i);
    }
    if (tmp == NULL && visited[i] == false){
        printf("case3\n");
        visited[i] = true;
        ///
        //加入stack 中
        if (isFull(stk) == false)
            push_in_stk(i);
        printf("stack now is : %d\n", peek(stk));
        ///
        for (int j = 0; j < V; j++){
            printf("visited[%d] = %d\n", j , visited[j]);
        }
        printf("\n");
    }

//    for (int k = 0 ; k< V;k++){
//        printf("stk[%d] = %d", k, stk[k]);
//    }
}

void traversal (int V, bool visited[]){
    int c = V;
    while (c--){
        visited[c] = false;
    }
//    printf("initial\n");
//    for (int j = 0; j < V; j++){
//        printf("visited[%d] = %d\n", j , visited[j]);
//    }
    for (int i = 0; i < V; i++){
        if ( visited[i] == false){
            visited[i] == true;
            printf("\ninto DFS\n");
            DFS(i,V, visited);
        }
    }
}
/////////////////////第一次DFS/////////////////

///////////第二次DFS///////////////////


void DFS_2 (int i, int V, int SCC_group, bool visited_2[] , int SCC[]){
    struct AdjListNode* tmp = rev_gph->array[i].head; //開始走反過來的graph
    while (tmp != NULL && visited_2[i] == false){
        visited_2[i] = true;
        DFS_2( tmp->dest, V, SCC_group, visited_2, SCC);
        SCC[i] = SCC_group;
        tmp = tmp->next;
    }
    if (tmp != NULL && visited_2[i] == true){
        printf("already visited_2 %d .\n", i);
    }
    if (tmp == NULL && visited_2[i] == false){
        visited_2[i] = true;
        SCC[i] = SCC_group;
    }
}

void traversal_2 (int V, bool visited_2[], int SCC[] ){
    int c = V;
    while (c--){
        visited_2[c] = false;
    }
    while(isEmpty(stk) == false){
        int pp = pop(stk);
        if (visited_2[pp] == false){
            visited_2[pp] = true;
            SCC[pp] = pp;
            DFS_2( pp, V, pp, visited_2 , SCC);// 利用第一個跑進去作DFS的數字做為SCC group的代稱，
            //例如node 1 2 3是相同的SCC，且第一個進去DFS的是node 2則 SCC[1] == SCC[2] == SCC[3] == 2
        }
    }
}

///////////第二次DFS///////////////////


int main()
{
//
//    int V, E;
//    scanf("%d %d", &V, &E);
//    //for DFS
//    bool visited[V];
//    bool visited_2[V];
//    stk = create_stack(V);
//    graph = createGraph(V);
//    rev_gph = createGraph(V);
//
//    int arc[E][2];
//
//    int SCC[V];

//    int src, dest;
//    int tmp_E = E;
//    int i = 0;
//    while (E--){
//        scanf("%d %d", &src, &dest);
//        addEdge(graph, src, dest);
//        arc[i][1] = src;
//        arc[i][0] = dest;
//        i++;
//    }
//    //printGraph(graph);
//    ///
//    //將邊全部反過來
//    i = 0;
//    while (tmp_E --){
//        addEdge(rev_gph,arc[i][0], arc[i][1]);
//        i++;
//    }
//    //printGraph(rev_gph);
//    ///
//
//
//
//    traversal(V, visited);
//
////    printf("print out the stack\n");
////    for (int i = 0; i < V; i++){
////        printf("%d " ,pop(stk));
////    }
////    printf("\n");

    return 0;
}
