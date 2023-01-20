#ifndef SETS_FILE
#define SETS_FILE

typedef struct card card;
struct card{
    char suit;  // suit of card
    int num;    // number (or face) of card 5->5, J->11, A->14
    card * next;
};

struct deck{
    card * head;
    card * tail;
};
typedef struct deck deck;

struct player{
    card * hand;
    int card_count;
    char * name;
    int bank;
};
typedef struct player player;

int check_hand(player * playerlist, int player);
void load_cards(player * P, int player, int cards_nums[], char cards_suit[]);
int two_kind(int nums[]);
int two_pair(int nums[]);
int three_kind(int nums[]);
int four_kind(int nums[]);
int straight(int nums[]);
int flush(char suits[]);
int full_house(int nums[]);
int straight_flush(int nums[], char suits[]);
int royal_flush(int nums[], char suits[]);
void print_result(int i, int player);


#endif
