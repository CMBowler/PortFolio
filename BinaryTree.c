// Sort a list of 100.000 books into a data structure which allows for
// both fast insertion and searching.. (Binary Tree Method)
// On top of this create a method to balance the tree for efficiency of insertion and searching

//#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define list_len 131071

typedef struct Node Node;
struct Node{
    unsigned doc_id;   // unique identifier for the document
    char   *name;          // file name of the document    
    int    word_count; 
	struct Node * left;    // number of words in the document      
    struct Node * right;   // pointer to the next node in the list
	int level;
};

//declare vars
Node * root = NULL;
int count, count_left, count_right, curr_diff, collisions;
int min_level, max_level, total_inserts;
float total_levels, total_routes, std_dev_sum;
float ave_level, stdev;

int bstdb_init(){
	//initialise vars
	count = 0;
	collisions = 0;
	total_routes = 0;
	total_levels = 0;
	max_level = 0;
	min_level = __INT32_MAX__;
	ave_level = 0;
	total_inserts = 0;
	std_dev_sum = 0;
	return 1;
}

int hash_address(unsigned int key, char * name, int attempt){
	unsigned long int long_key = 0;
	while(*name){
		long_key = ((long_key + attempt * (key * (*name))) % list_len);
		name++;
	}
	return (int)long_key;
}

Node * read_in(char * name, int word_count, int attempt){
	Node * node = (Node*)malloc(sizeof(Node));
	int len = strlen(name)+1;
	node->name = calloc(len, sizeof(char));
	if(node->name) strcpy(node->name, name);
	else printf("error in calloc name\n");

	node->word_count = word_count;
	node->left = NULL;
	node->right = NULL;
	
	node->level = 0;

	node->doc_id = hash_address(word_count, name, attempt);

	return node;
}

int insert(Node * new, Node * root){
	// had to replace recursive method with iterative method
	// due to compiler warnings.. (worked fine..)
	Node * curr = root;
	
	while(curr->doc_id != new->doc_id){
		new->level = new->level + 1;
		if(new->doc_id < curr->doc_id){
			if(curr->left) curr = curr->left;
			else {
				curr->left = new;
				return 0;
			}
		} else if(new->doc_id > curr->doc_id){
			if(curr->right) curr = curr->right;
			else {
				curr->right = new;
				return 0;
			}
		}
	}
	return 1;
	
}

int bstdb_add (char *name, int word_count) {

	int attempt = 1;
	Node * new = read_in(name, word_count, attempt);
	if(root == NULL){
		root = new;
		return new->doc_id;
	} else {
		while(insert(new, root) != 0){
			attempt++;
			collisions++;
			new->level = 0;
			new->doc_id = hash_address(new->word_count, new->name, attempt);
		}
		//printf("node: %i\n", new->doc_id);
		return new->doc_id;
	}
}

Node * find_node(Node * node, int id){
//had to replace recursive method with iterative due to comiler warning..
	Node * curr = node;
	while(curr->doc_id != id){
		if(id < curr->doc_id) curr = curr->left;
		else if(id > curr->doc_id) curr = curr->right;

		if(curr == NULL) return NULL;
	}
	return curr;
}

int bstdb_get_word_count(int doc_id){
	//does what it says on the tin..
	Node * node = find_node(root, doc_id);
	if(node != NULL){
		return node->word_count;
	} else return -1;
}

char * bstdb_get_name ( int doc_id ) {
	// does what it says on the tin..
	Node * node = find_node(root, doc_id);
	if(node != NULL){
		return node->name;
	} else return NULL;
}

void get_ave_depth(Node * node){

	total_inserts++;
	
	if(node->left != NULL) get_ave_depth(node->left);
	if(node->right != NULL) get_ave_depth(node->right);
	
	if(node->right == NULL && node->left == NULL){
		total_routes++;
		if(node->level > max_level) max_level = node->level;
        if(node->level < min_level) min_level = node->level;
		total_levels = total_levels + node->level;
	}
}

void get_stdev(Node * node){
	
	if(node->left) get_stdev(node->left);
	if(node->right) get_stdev(node->right);

	if(node->right == NULL && node->left == NULL){
		std_dev_sum = std_dev_sum + pow(2, ((double)node->level - ave_level));
	}
}

// resets level attribute in nodes..
void re_level(Node * node, int level){
	if(node != NULL){
		node->level = level;
		level++;
		re_level(node->left, level);
		re_level(node->right, level);
	}
}

//store left/right weights in global vars...
void check_pivot(Node * node, int value){
	if(node->doc_id < value) count_left++;
	else if(node->doc_id > value) count_right++;

	if(node->left != NULL) check_pivot(node->left, value);
	if(node->right != NULL) check_pivot(node->right, value);
}

Node * find_pivot(Node * node){
	count_left = 0;
	count_right = 0;
	check_pivot(node, node->doc_id);
	int prev_diff, new_diff = abs(count_left - count_right);
	Node * prev, * curr = node;
	//loop until best balance node is found..
	do {
		//init
		prev_diff = new_diff;
		prev = curr;

		if(count_left == count_right){
			return prev;
		}
		else if(count_left > count_right){
			if(curr->left != NULL) curr = curr->left;
			else return curr;
		}
		if(count_left < count_right){
			if(curr->right != NULL) curr = curr->right;
			else return curr;
		}
		count_left = 0;
		count_right = 0;
		//get left/right weights
		check_pivot(node, curr->doc_id);
		new_diff = abs(count_left - count_right);
	} while(prev_diff > new_diff || new_diff > 1);
	
	return prev;
}

// on path to new root, insert every node into new root,
// sever pointers as well.. 
void re_root(Node * old_root, Node * new_root, Node * parent){
	//init
	Node * curr = old_root;
	Node * prev;
	int address = new_root->doc_id;
	//re_root
	while(curr != new_root){
		prev = curr;
		if(curr->doc_id > address){
			if(curr->left) curr = curr->left;
			prev->left = NULL;
		} else { //if(curr->doc_id > address)
			if(curr->right) curr = curr->right;
			prev->right = NULL;
		}
		//insert sub tree into new root..
		if(insert(prev, new_root) == 1) printf("insert error\n");
	}
	//assign new sub-root to parent
	if(parent == NULL){
		root = new_root;
	}
	else{
		if(new_root->doc_id < parent->doc_id) parent->left = new_root;
		else if(new_root->doc_id > parent->doc_id) parent->right = new_root;
	}
}

//balance the tree (recursively)
void balance(Node * node, Node * parent){
	//get pivot node
	Node * pivot = find_pivot(node);
	//make pivot new root
	re_root(node, pivot, parent);

	if(pivot->left) balance(pivot->left, pivot);
	if(pivot->right) balance(pivot->right, pivot);
}

void bstdb_stat ( void ) {
	
	printf("Collisions: %i\n", collisions);

	get_ave_depth(root);
	ave_level = total_levels / total_routes;

	printf("min/max level: %i / %i\n", min_level, max_level);
	printf("average length of route: %f\n", ave_level);

	get_stdev(root);
	stdev = std_dev_sum / total_inserts;
	stdev = sqrt(stdev);
	printf("Standard Deviation of Levels: %f\n", stdev); 

	// balance...
	
	printf("balanced tree:\n");
	balance(root, NULL);

	re_level(root, 0);
	//reset vars..
	total_inserts = 0;
	total_levels = 0;
	total_routes = 0;
	std_dev_sum = 0;
	max_level = 0;
	min_level = __INT32_MAX__;

	get_ave_depth(root);
	ave_level = total_levels / total_routes;

	printf("min/max level: %i / %i\n", min_level, max_level);
	printf("average length of route: %f\n", ave_level);

	get_stdev(root);
	stdev = sqrt(std_dev_sum/total_inserts);
	printf("Standard Deviation of Levels: %f\n", stdev); 
	//
	return;
}

void delete(Node * node){
	if(node->left) delete(node->left);
	if(node->right) delete(node->right);
	free(node);
}

void bstdb_quit ( void ) {
	delete(root);
}


