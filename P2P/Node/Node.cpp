#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Tracker.h"
#include "Node.h"
#include "Routing.h"

#define IP_LEN 20
#define MX_STR_LEN 100
#define ROW_LEN 80
#define nList_size 5000

// globals 

edge * EdgeList[nList_size] = {NULL};
node * NodeList[nList_size] = {NULL};
// include func for...
//  - parsing recieved msg
//  - build send msg
//  - route msg
//  - vector routing

using namespace std;


int Node::init_node(char * argv[]){
    
    address = atoi(argv[1]);
    printf("Port Set: %i\n", address);
    
    printf("loading node info...\n");
    if(!load_node_info(argv[2])){
        printf("Err loading node info\n");
        return 0;
    }
    printf("Loading nodes.. \n");
    address_book = load_nodes(argv[3]);
    printf("Loading edges...\n");
    edge_list = load_edges(argv[4]);
    printf("Loading list of files...\n");
    load_files(argv[5]);
    return 1;
}

int Node::load_node_info(char *fname){
    FILE * csv = fopen(fname, "r");
    // set check var
    file->id = 0;
    char row[ROW_LEN];
    char * token;
    fgets(row, ROW_LEN, csv);

    while(!feof(csv)){
        // find the corresponding row in the node info datasheet...
        token = strtok(row, ",");
        while(atoi(token) != address){
            fgets(row, ROW_LEN, csv);
            token = strtok(row, ",");
        }
        // read in relative info...
        token = strtok(NULL, ",");
        // node name
        strcpy(name, token);
        printf("Imported Node name: %s\n", name);
        // file num
        token = strtok(NULL, ",");
        file->id = atoi(token);
        printf("Imported File id: %i\n", file->id);
        // file data
        token = strtok(NULL, "\n");
        file->char_count = strlen(token);
        strcpy(file->word, token);
        printf("Imported Dataset: %s\n", file->word);
        break;
    }
    if(!file->id) return 0;
    printf("Loaded data into node\n");
    return 1;
}        

node * Node::load_nodes (char *fname){
    // init
    FILE * csv = fopen(fname, "r");
    char row[MX_STR_LEN];
    fgets(row, MX_STR_LEN, csv);
    node * N = (node*)malloc(sizeof(node));
    node * temp, * head = N;
    head->next = NULL;
    // go though the file and add all nodes to the list.
    while(!feof(csv)){
        node * N = (node*)malloc(sizeof(node));
        N->id = atoi(row);
        temp = head;
        N->next = head;
        head = N;
        fgets(row, MX_STR_LEN, csv);
    }
    printf("Loaded nodes\n");
    return head;
}

edge ** Node::load_edges (char *fname){

    FILE * csv = fopen(fname, "r");

    char row[MX_STR_LEN];
    char * token;

    fgets(row, MX_STR_LEN, csv);


    while(!feof(csv)){
        edge * D1 = (edge*)malloc(sizeof(edge));
        edge * D2 = (edge*)malloc(sizeof(edge));
        fgets(row, MX_STR_LEN, csv);

        D1->e_next = NULL;
        D2->e_next = NULL;

        edge * adj_head;
        // char * buffer = (char*)malloc(MX_STR_LEN * sizeof(char));
        token = strtok(row, ",");
        for(int i=0; token != NULL; i++){
            switch (i) {
            case 0: // V1
                // from D1 to D2..
                adj_head = EdgeList[atoi(token)];
                D1->id = atoi(token);
                if(adj_head)
                    D2->e_next = adj_head;
                EdgeList[atoi(token)] = D2;
                break;
            case 1: // V2
                // from D2 to D1
                D2->id = atoi(token);
                adj_head = EdgeList[atoi(token)];
                if(adj_head)
                    D1->e_next = adj_head;
                EdgeList[atoi(token)] = D1;
                break;
            case 2: //weight
                D1->weight = atoi(token);
                D2->weight = atoi(token);
                break;
            default:
                break;
            }
            token = strtok(NULL, ",");
        }
        //printf("Edge: %i <-> %i\n", D1->id, D2->id);
    }
    printf("Loaded edges\n");
    return &(EdgeList[0]);
} 

void Node::load_files(char *fname){
    FILE * csv = fopen(fname, "r");
    char row[MX_STR_LEN];
    fgets(row, MX_STR_LEN, csv);
    int index = 0;
    while(!feof(csv)){
        file_list[index] = atoi(row);
        // printf("file added: %i\n", atoi(row));
        index++;
        fgets(row, MX_STR_LEN, csv);
    }
    printf("Loaded files\n");
}

int Node::book_update(int node_id, int action){
    // action = 1 -> add, action = 0 -> remove
    if(action){
        // Add Node 
        node * temp = address_book;
        node * new_node = (node*)malloc(sizeof(node));
        // assign attributes to new node
        new_node->id = node_id;
        new_node->next = temp;
        // set new node as head of addressbook
        address_book = new_node;
    }
    else {
        // Remove node.
        node * curr = address_book;
        node * temp;
        while(curr){
            if(curr->next->id == node_id){
                curr->next = temp;
                curr->next = curr->next->next;
                delete(temp);
            }
        }
    }
    printf("Nodes updated\n");
    return 1;
}  

int Node::add_file(char * dataseg){ 
    //create new data package...
    dataset * new_data = (dataset*)malloc(sizeof(dataset));
    new_data->word = (char*)malloc(MX_STR_LEN * sizeof(char));
    if(data){
        // add datagram to the list of data
        new_data->next = data;
    }
    data = new_data;
    // parse msg
    char * parse = strtok(dataseg, ".");
    printf("Adding file to node %s..", parse);
    // read in file ID
    parse = strtok(NULL, ".");
    data->id = atoi(parse);
    // read in seg ID
    parse = strtok(NULL, ".");
    data->seg = atoi(parse);
    // read in data
    parse = strtok(NULL, "\0");
    strcpy(data->word, parse);

    printf(" file read in\n");

    return 1;

}

int Node::share_file(){
    // parse the file into x amount of pieces.
    printf("create data packets\n");
    int seg = 100;
    int num_of_segs = 10;
    int seg_size = file->char_count/num_of_segs;
    int index = 0;
    for(int i=0; i<num_of_segs; i++){

        string msg;
        msg = msg + to_string(rendezvous(file->id, (seg+i),
                              address_book, address));
        // cout << msg << endl;
        msg = msg + "." + to_string(file->id);
        // cout << msg << endl;
        msg = msg + "." + to_string(seg + i) + ".";
        //cout << msg << endl;

        // read in data

        if(i == num_of_segs-1){
            for(int j=index; j<file->char_count; j++){
                msg = msg + file->word[j];
            }
            index = index + seg_size;
            cout << msg << endl;
        }
        else{
            for(int j=index; j<index+seg_size; j++){
                msg = msg + file->word[j];
            }
            index = index + seg_size;
            cout << msg << endl;
        }
        
    }
    // special case final seg.


    return 1;
}

// getters

char * Node::return_file_seg(int dest_port, int file_id, int file_seg){
    dataset * curr = data;
    char data_seg[MX_STR_LEN];
    char buffer[MX_STR_LEN];
    while(curr){
        if(curr->id == file_id && curr->seg == file_seg){
            // build msg.
            sprintf(buffer, "%i", dest_port);
            strcat(data_seg,buffer);
            strcat(data_seg, ".");
            sprintf(buffer, "%i", curr->id);
            strcat(data_seg, buffer);
            strcat(data_seg, ".");
            sprintf(buffer, "%i", curr->seg);
            strcat(data_seg, buffer);
            strcat(data_seg, ".");
            strcpy(buffer, curr->word);
            strcat(data_seg, buffer);
            return data_seg;
        }
        curr = curr->next;
    }
    printf ("No data seg found!\n");
    return NULL;

}

unsigned Node::get_address(){return address;}
node * Node::get_node_list(){return address_book;}
edge ** Node::get_edge_list(){return edge_list;}
dataset * Node::get_file(){return file;}
dataset * Node::get_data_list(){return data;}


int main(int argc, char *argv[]){
	Node N1;
	if(!N1.init_node(argv)){
		printf("Err in init node (port id: %i)\n", atoi(argv[1]));
	}

    node * list = N1.get_node_list();
    node * curr = list;
    edge ** e_arr = (N1.get_edge_list());
    edge * e_head;

    // while(curr){
    //     printf("Port: %i\n", curr->id);
    //     // printf("Connections:\n");
    //     // e_head = *(e_arr + curr->id);
    //     // while(e_head){
    //     //     printf(" -> %i", e_head->id);
    //     //     e_head = e_head->e_next;
    //     // }
    //     // printf("\n");
    //     curr = curr->next;
    // }
    if(!N1.share_file()){
        printf("err: sharing file\n");
    }
    
    int end;
    printf("\nshortest path proof\n\n");
    cout << "Destination: ";
    cin >> end;
    if(end == N1.get_address()){
        printf("Already at node\n");
    }
    else{
        int next_hop;
        list = N1.get_node_list();
        while(1){
            if(list->id == end){
                next_hop = shortest_path(N1.get_address(), end, 
                            N1.get_edge_list(), N1.get_node_list());
                printf("Next Hop: %i\n", next_hop);
                break;
            }
            list = list->next;
            if(list == NULL){
                printf("Port node found in list of known ports!\n");
                break;
            }
        }
    }
   
    return 0;
}


// nodes know about other nodes throught the 'address book', DHT
// the DHT could be organised by a central authourity but for the purpose and functionality of this network
// a more distributed approach is preferred... 
// A change in the DHT in one node will be pinged to each node in the network, then each node will compare the TIEMSTAMP on its DHT with the one it has just been sent
// and will choose the newest one as its list... 

//book_date: