#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define SIZE 300005
//h50000V 150000
int total_counts = 0;
int pan_array[100000];
int visited[50002][102];

struct queue {
    int items[SIZE];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

struct node{
    int vertex;
    struct node* next;
};

struct node* createNode(int);

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int* visited;
};

struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
void bfs(struct Graph* graph, int startVertex, int pan_array[], int V, int L, int fin_lel);


struct Graph* graph;
int main()
{
    int V, E, L, G, fin_lel;
    scanf("%d %d %d %d", &V, &E, &L, &G);
    graph = createGraph(V);
    int tmp = 0;
    int plc, pan, src, dest;
    fin_lel = L;
    for (int i = 0; i < 100000; i++)
        pan_array[i] = 0;
    int a = G;
    while (G--){
        scanf("%d %d", &plc, &pan);
        if (pan_array[plc] == 0 && pan_array[plc] != -10)
            pan_array[plc] = pan;
        else
            pan_array[plc] = -10;
    }
    while (E--){
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    bfs(graph, 0, pan_array, V, L, fin_lel);
    if (total_counts != -1)
        printf("%d", total_counts + L - 1);// 只吃 L-1 次
    else
        printf("-1");
    return 0;
}
void bfs(struct Graph* graph, int startVertex, int pan_array[], int V, int L, int fin_lel) {
    int q_num ;
    struct queue* q = createQueue();
    for (int i = 0; i < 50002; i++){
        for (int j = 0; j < 102; j++){
            visited[i][j] = 0;
        }
    }
    visited[startVertex][1] = 1;
    enqueue(q, startVertex);
    enqueue(q, 1);
    enqueue(q, -5);
    bool in_to_update_level = false;
    int currentVertex, tmp_level;
    while(!isEmpty(q) && tmp_level != fin_lel){
        printf("前：\n");
        printQueue(q);

        currentVertex = dequeue(q);
        if (currentVertex != -5){
            tmp_level = dequeue(q);
        }
        if (currentVertex > 0 && pan_array[currentVertex] == tmp_level){
            in_to_update_level = true;
        }
        if(currentVertex != -5){
            struct node* temp = graph->adjLists[currentVertex];
            while(temp) {
                int adjVertex = temp->vertex;
//                printf("pan_array[%d] = %d, tmp_level = %d\n", adjVertex, pan_array[adjVertex], tmp_level);
                if (in_to_update_level == true){
                    tmp_level ++;
                    in_to_update_level = false;
                }
//                printf("visited[%d][%d] = %d\n" ,adjVertex, tmp_level, visited[adjVertex][tmp_level]);
                if(visited[adjVertex][tmp_level] == 0 && ( pan_array[adjVertex] == 0 || pan_array[adjVertex] == tmp_level)){
//                    printf("here~~~~~~~~`\n");
                    visited[adjVertex][tmp_level] = 1;
                    enqueue(q, adjVertex);
                    enqueue(q, tmp_level);
                }
                if (visited[adjVertex][tmp_level -1] == 0 && pan_array[adjVertex] == tmp_level -1 && tmp_level != 1){
                    visited[adjVertex][tmp_level-1] = 1;
                    enqueue(q, adjVertex);
                    enqueue(q, tmp_level-1);
                }
                temp = temp->next;
            }
            printQueue(q);
            printf("-----------\n");
        }
        else {
            total_counts ++;
            if (!isEmpty(q)){
                enqueue(q, -5);
            }
        }
    }
    if (!isEmpty(q))
        q_num = dequeue(q);

    if ( tmp_level != fin_lel){
        total_counts = -1;
    }
}

///

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}


int isEmpty(struct queue* q) {
    if(q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue* q, int value){
    if(q->rear == SIZE-1)
        printf("");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue* q){
    int item;
    if(isEmpty(q)){
//        printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            //printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
//        printf("Queue is empty");
    } else {
        printf("Queue contains : ");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}
