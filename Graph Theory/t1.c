// graph system using adjacency lists
#include "t1.h"
#include <stdio.h>
#include <stdlib.h>

int num_edges = 0;
int init_DFS = 0;
int end_DFS = 0;

void init_Graph(Graph * g, int size){
    for(int i=0; i<size; i++){
        g->E[i] = NULL;
        g->bfs_visited[i] = 0;
        g->dfs_visited[i] = 0;
    }
}

typedef struct Queue Queue;
struct Queue{
    Node * head;
    Node * tail;
};
Queue * q; //global

Graph * create_graph(int num_nodes){
    // create struct..
    Graph * new_graph = malloc(sizeof(Graph));
    new_graph->E = malloc(num_nodes * sizeof(Node));
    new_graph->V_count = num_nodes;
    new_graph->bfs_visited = malloc(num_nodes * sizeof(int));
    new_graph->dfs_visited = malloc(num_nodes * sizeof(int));

    init_Graph(new_graph, num_nodes);

    return new_graph;
}

Queue * create_queue(int size){
    Queue * newQ = malloc(sizeof(Queue));
    newQ->head = NULL;
    newQ->tail = NULL;
    
    return newQ;
}
// Utility Functions
static char int2char ( int i){
    if( i > 25){
        return '\0';
    }
    return 'A' + i;
}

void enqueue(Queue * q, int value){
    Node * new = malloc(sizeof(Node));
    new->to = value;
    new->link = NULL;
    
    if(q->head){
        (q->tail)->link = new;
        q->tail = new;
    } else {
        q->head = new;
        q->tail = new;
    }
}

int dequeue(Queue * q){
    int value;
    Node * temp;
    if(!q->head){
        value = -1;
    } else {
        temp = q->head;
        value = (q->head)->to;
        q->head = (q->head)->link;
    }
    free(temp);
    return value;
}


void add_edge(Graph * g, int from, int to){
    
    //create new struct..
    Node * new = malloc(sizeof(Node));
    new->to = to;
    new->link = NULL;
    //place node in linked list of adjacent nodes..
    if(g->E[from])
        new->link = g->E[from];
    g->E[from] = new;

    num_edges++;
}

void bfs(Graph* g, int origin){
    printf("BFS: \n");
    int value, vertex;
    
    q = create_queue(num_edges);

    g->bfs_visited[origin] = 1;
    enqueue(q, origin);

    while(q->head){

        value = dequeue(q);
        printf("%c\n", int2char(value));

        Node * curr = g->E[value];
        while (curr) {
            vertex = curr->to;
            if(g->bfs_visited[vertex] == 0){
                g->bfs_visited[vertex] = 1;
                enqueue(q, vertex);
            }
            curr = curr->link;
        }
    }
    printf("\n");
}

void dfs(Graph * g, int origin){
    if(!init_DFS){
        printf("DFS: \n");
        init_DFS++;
    }
    Node * adj_list = g->E[origin];
    Node * curr = adj_list;
    g->dfs_visited[origin] = 1;
    printf("%c\n", int2char(origin));

    while (curr != NULL){
        if(g->dfs_visited[curr->to] == 0){
            dfs(g, curr->to);
        }
        curr = curr->link;
    }

}

void delete_graph(Graph * g){

    free(g->bfs_visited);
    free(g->dfs_visited);
    Node * curr, * temp;
    for(int i=0; i<g->V_count; i++){
        curr = g->E[i];
        while(curr){
            temp = curr;
            curr = curr->link;
            free(temp);
        }
    }
    free(g->E);
    free(g);
    curr = q->head;
    while(curr){
        temp = curr;
        curr = curr->link;
        free(curr);
    }
    free(q);
}