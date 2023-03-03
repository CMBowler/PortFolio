#ifndef NODE_H
#define NODE_H

#define nList_size 5000
#define MX_STR_LEN 100

#include <string>
#include "Tracker.h"
#include "Routing.h"

class Node {

    private:
        unsigned address;
        char * name;
        node * address_book;
        edge ** edge_list;
        dataset * data;
        dataset * file;
        int file_list[100];
        int * map;
        //book_date: yy/mm/dd/hh/mm/ss/..
        unsigned book_date;
    public:
        //constructs node
        Node(){

            address = 0;

            name = (char*)malloc(MX_STR_LEN * sizeof(char));

            address_book = NULL;

            edge_list = NULL;

            data = (dataset*)malloc(sizeof(dataset));

            file = (dataset*)malloc(sizeof(dataset));

            file->id = 0;
            file->seg = 0;
            file->next = NULL;
            file->word = (char*)malloc(MX_STR_LEN * sizeof(char));

            data->next = NULL;

            map = (int*)malloc(nList_size * sizeof(int));

            book_date = 0;

        }
        // initialise node
        int init_node(char * argv[]);
        // load nod info intoc correct attributes
        int load_node_info (char *fname);
        //loads the vertices from the CSV file of name fname
        node * load_nodes (char *fname); 
        //loads the edges from the CSV file of name fname
        edge ** load_edges (char *fname);
        // loads list of available files
        void load_files (char * fname);
        // get segment of file from data bank
        char * return_file_seg(int dest_port, int file_id, int file_seg);

        int book_update(int node_id, int action);
        
        int share_file();

        int add_file(char * dataseg);

        // getters 

        unsigned get_address();
        node * get_node_list();
        edge ** get_edge_list();
        dataset * get_file();
        dataset * get_data_list();

};

#endif