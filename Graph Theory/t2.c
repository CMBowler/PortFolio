#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define V_list_size 10000
#define stringLength 50

typedef struct Vertex Vertex;
typedef struct Node Node;
typedef struct Graph Graph;

struct Vertex{
    int vertex;
    Vertex * q_next;
    char * name;
    double lng;
    double lat;
};

struct Node{
    //Node contains pointer to adjacent Vertex and link to next adjacent Vertex.
    Vertex * V;
    Node * adj_link;
    int weight;
};

struct Graph {
    Vertex * V;
    Node ** E;
};

//globals 

Vertex * V_list[V_list_size];
Node * Edge_list[V_list_size];

int num_egdes = 0;

//parser..

char * remove_quote(char * input){
    char * buffer = malloc(stringLength * sizeof(char));
    int i, j=0;
    for(i=0; input[i] != '\0'; i++){
        if(input[i] != '\"'){
            buffer[j] = input[i];
            j++;
        }
        else;
    }
    buffer[j+1] = '\0';
    return buffer;
}

//loads the edges from the CSV file of name fname
int load_edges (char *fname){
    FILE * csv = fopen(fname, "r");

    const int row_len = 50;
    char row[row_len];
    char * token;

    fgets(row, row_len, csv);

    while(!feof(csv)){
        Node * D1 = malloc(sizeof(Node));
        Node * D2 = malloc(sizeof(Node));
        fgets(row, row_len, csv);

        Node * adj_head;
        char * buffer = malloc(stringLength * sizeof(char));
        token = strtok(row, ",");
        for(int i=0; token != NULL; i++){
            strcpy(buffer, remove_quote(token));
            switch (i) {
            case 0: // V1
                // from D1 to D2..
                adj_head = Edge_list[atoi(buffer)];
                if(adj_head)
                    D2->adj_link = adj_head;
                Edge_list[atoi(buffer)] = D2;

                D1->V = V_list[atoi(buffer)];
                break;
            case 1: // V2
                // from D2 to D1
                adj_head = Edge_list[atoi(buffer)];
                if(adj_head)
                    D1->adj_link = adj_head;
                Edge_list[atoi(buffer)] = D1;

                D2->V = V_list[atoi(buffer)];
                break;
            case 2: //weight
                D1->weight = atoi(buffer);
                D2->weight = atoi(buffer);
                break;
            default:
                break;
            }
            token = strtok(NULL, ",");
        }
        num_egdes++;
        // Node* curr = Edge_list[D1->V->vertex];
        // //printf("%i: ", D1->V->vertex);
        // while(curr){
        //     //printf("%i -> ", curr->V->vertex);
        //     curr = curr->adj_link;
        // }
        //printf("\n");
    }
    printf("Loaded %i edges\n", num_egdes);
    return 1;
} 
//loads the vertices from the CSV file of name fname
int load_vertices (char *fname){
    FILE * csv = fopen(fname, "r");
    
    int v_count = 0;
    const int row_len = 100;
    char row[row_len];
    char * token;
    fgets(row, row_len, csv);


    while(!feof(csv)){
        Vertex * V = malloc(sizeof(Vertex));
        V->name = malloc(stringLength * sizeof(char));
        V->q_next = NULL;
        fgets(row, row_len, csv);
        char * buffer = malloc(stringLength * sizeof(char));
        token = strtok(row, ",");

        for(int i=0; token != NULL; i++){
            strcpy(buffer, remove_quote(token));
            switch (i) {
            case 0: //StopID
                V->vertex = atoi(buffer);  
                break;
            case 1: //name
                strcpy(V->name, buffer);
                break;
            case 2: // latitude
                V->lat = atof(buffer);
                break;
            case 3: // longitude
                V->lng = atof(buffer);
                break;
            default:
                break;
            }
            token = strtok(NULL, ",");
        }

        if(V_list[V->vertex])
            printf("Err Vertex ID collision\n");
        V_list[V->vertex] = V;
        v_count++;
    }
    printf("Loaded %i vertices\n", v_count);
    return 1;
} 

// queue..

typedef struct Queue Queue;
struct Queue{
    Vertex * head;
    Vertex * tail;
};
//global q
Queue * q;

Queue * create_queue(){
    Queue * newQ = malloc(sizeof(Queue));

    newQ->head = NULL;
    newQ->tail = NULL;
    
    return newQ;
}

int isEmpty(Queue * q){
    if(q->head == NULL)
        return 1;
    else return 0;
}

void priority_q(Queue * q, Vertex * v, int * dist){
    Vertex * curr = q->head;
    Vertex * prev = NULL;
    if(curr == NULL)
        q->head = v;
    else{
        // find node position in weighted priority queue
        while(dist[curr->vertex] > dist[v->vertex] || curr != NULL){
            prev = curr;
            curr = curr->q_next;
        }
        // insert node
        prev->q_next = v;
        v->q_next = curr;
    }
}

void de_priority_q(Queue * q, Vertex * v, int * dist){
    Vertex * curr = q->head;
    Vertex * prev = NULL;
    //find changing node
    while(curr){
        if(curr == v){
            prev->q_next = curr->q_next;
            break;
        }
        prev = curr;
        curr = curr->q_next;
    }
    printf("found vertex\n");
    //re insert w/ new priority
    priority_q(q, v, dist);
}

void enqueue(Queue * q, Vertex * v){
    if(isEmpty(q)){
        q->head = v;
        q->tail = v;
    } else {
        q->tail->q_next = v;
        q->tail = v;
    }
}

Vertex * dequeue(Queue * q){
    Vertex * node;
    if(isEmpty(q)){
        node = NULL;
    } else {
        node = (q->head);
        if(q->head)
            q->head = (q->head)->q_next;
    }
    return node;
}

int search_Edges( int u, int v){
    //return weight if edge exists..
    Node * curr = Edge_list[u];
    while(curr){
        if(curr->V->vertex == v){
            return curr->weight;
        }
        curr = curr->adj_link;
    }
    return 0;
}

int min_distance(int dist[], Vertex * prev[]){
    int min = __INT_MAX__, min_index;
    for(int v=0; v < V_list_size; v++){
        if(prev[v] == NULL && dist[v] < min){
            min = dist[v];
            min_index = v;
        }
    }
    //printf("min_index: %i\n", min_index);
    return min_index;
}
// prints the shortest path between startNode and endNode, if there is any
void shortest_path(int startNode, int endNode){
    //dijkstra algorithm..
    //init
    q = create_queue();
    int dist[V_list_size];
    Vertex * prev[V_list_size];
    int map[V_list_size];

    for(int i=0; i<V_list_size; i++){
        dist[i] = __INT_MAX__; //set as 'unexplored'
        prev[i] = NULL;
    }
    dist[startNode] = 0;
    int u;

    for (int i=0; i<V_list_size; i++){
        // operate if vertex exists.
        if(V_list[i]){
            u = min_distance(dist, prev);
            prev[u] = V_list[u];
            for(int v=0; v<V_list_size; v++){
                if(!prev[v] && search_Edges(u,v)
                    && dist[u] != __INT_MAX__  
                    && dist[u] + search_Edges(u,v) < dist[v]){
                    dist[v] = dist[u] + search_Edges(u,v);
                    map[v] = u;
                }
            }
        }
    }
    // if(prev[endNode])
    //     printf("Dist from star to end = %i\n", dist[endNode]);
    // else printf("No route!\n");

    u = endNode;
    //stack for printing..
    q->head = V_list[u];
    V_list[u]->q_next = NULL;
    u = map[u];
    while(u != startNode){
        V_list[u]->q_next = q->head;
        q->head = V_list[u];
        u = map[u];
    }
    V_list[u]->q_next = q->head;
    q->head = V_list[u];
    Vertex * curr = q->head;
    while(curr){
        printf("%i %s\n", curr->vertex, curr->name);
        curr = curr->q_next;
    }
} 
// frees any memory that was used
void free_memory ( void ) {
    Node * curr, * temp;
    free(q);
    for(int i=0; i<V_list_size; i++){
        free(V_list[i]);
        curr = Edge_list[i];
        while(curr){
            temp = curr;
            curr = curr->adj_link;
            free(temp);
        }
    }
}; 

//note to self.. reworked queue to be a linked list with h/t pointers
// make function removing 'u' node from q: u-> node with smallest dist in dist array..

//print function...