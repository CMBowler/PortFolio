#ifndef MODULE_TRACKER
#define MODULE_TRACKER

#include <vector>
// simulated package of data.
typedef struct dataset{
    int id;
    int seg;
    char * word;
    int char_count;
    dataset * next;
} dataset;

// list of nodes within the network, can be updated...
typedef struct node{
    int id;
    node * next;
    node * q_next;
} node;

// list of connections between nodes in the network
typedef struct edge{
    int id;
    int weight;
    edge * e_next;
} edge;

//Network Struct
typedef struct NETWORK{
    node * N;
    edge ** E;
} NETWORK;

// add a node to the node list
void list_add(node * new_node, node * head);

// remove a node from the list.. re allocate all the data from the node into the network...
void list_remove(node * old_node, node * head);

// choose the node to send a segment of a file to... highest weighed node wins...
int rendezvous(int file_key, int file_seg, node * head, int self);
 
// hash function develops a int based on input parameters... aim to be as distributed as possible among all possible outcomes...
int hash(int key, int seg, int node);

#endif

/*** end of file ***/