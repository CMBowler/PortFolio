#ifndef ROUTE_H_
#define ROUTE_H_

#include "Tracker.h"
#include "Node.h"


int shortest_path(int startNode, int endNode, edge ** e_list, node * n_list); // prints the shortest path between startNode and endNode, if there is any
void free_memory(void) ; // frees any memory that was used

#endif
