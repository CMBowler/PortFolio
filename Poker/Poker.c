#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Sets.h"
#include "Odds.h"

#define DECK_SIZE 52
char face[] = {'J', 'Q', 'K', 'A'};

void init_deck(deck * D){
    char suit[4] = {'H', 'D', 'C', 'S'};

    for (int i=0; i<4; i++){
        for(int j=1; j<15; j++){
            // define card
            card * C = malloc(sizeof(card));
            C->suit = suit[i];
            C->num = j;
            // add to stack
            if(D->head){
                C->next = D->head;
                D->head = C;
            } else {
                C->next = NULL;
                D->head = C;
                D->tail = C;
            }
        }
    }
    printf("Deck initialised.\n");
}

void print_deck(deck * D){
    card * curr = D->head;
    while(curr){
        printf("%c%i\n", curr->suit, curr->num);
        curr = curr->next;
    }
}

void shuffle(deck * D){

    card * curr = NULL;
    card * prev = NULL;

    for(int i=0; i<DECK_SIZE*38; i++){
        int j = rand()%DECK_SIZE;
        curr = D->head;
        while(j > 0 && curr->next != NULL){
            prev = curr;
            curr = curr->next;
            j--;
        }
        if(curr == D->head){
            D->head = curr->next;
            D->tail->next = curr;
            D->tail = curr;
            D->tail->next = NULL;
        } else if(curr == D->tail){
            continue;
        } else {
            prev->next = curr->next;
            D->tail->next = curr;
            D->tail = curr;
            D->tail->next = NULL;
        }
    }
    printf("Shuffled.\n");
}

card * pop(deck * D){
    if(D->head){
        card * top = D->head;
        D->head = D->head->next;
        return top;
    } else {
        printf("Deck Empty.");
        return NULL;
    }
}

player * init_players(int num_players){
    player * player_list = malloc((num_players + 1) * sizeof(player));
    for(int i=0; i<num_players; i++){
        player * P = (player_list + i);
        P->hand = NULL;
        P->bank = 1000;
        P->card_count = 0;
    }
    return player_list;
}

void deal(deck * D, player * player_list, int num_players){
    for(int i=1; i<=num_players; i++){
        player * P = (player_list + i);
        if(P->hand){
            card * new_card = pop(D);
            new_card->next = P->hand;
            P->hand = new_card;
        } else {
            P->hand = pop(D);
            P->hand->next = NULL;
        }
        P->card_count++;
    }
}

void house(deck * D, player * player_list, int num_players){
    player * H = player_list;
    if(H->hand){
        card * new_card = pop(D);
        new_card->next = H->hand;
        H->hand = new_card;
    } else {
        H->hand = pop(D);
        H->hand->next = NULL;
    }
    H->card_count++;
}

void print_hand(player * player_list, int num){
    for(int i=0; i<=num; i++){
        player * P = player_list + i;
        card * curr = P->hand;
        printf("Player %i: ", i);
        while(curr){
            if(curr->num > 10){
                printf("%c%c  ", curr->suit, face[(curr->num)-11]);
            } else {
                printf("%c%i  ", curr->suit, curr->num);
            }
            curr = curr->next;
        }
        printf("\n");
    }
}

int main(){
   
    deck * D = malloc(sizeof(deck));
    init_deck(D);
    //
    shuffle(D);
    //print_deck(D);
    int num_players = 3;
    //define players
    player * player_list = init_players(num_players);
    
    deal(D, player_list, num_players);
    deal(D, player_list, num_players);
    house(D, player_list, num_players);
    house(D, player_list, num_players);
    house(D, player_list, num_players);
    house(D, player_list, num_players);
    house(D, player_list, num_players);

    
    print_hand(player_list, num_players);
    for(int i=1; i<=num_players; i++){
        check_hand(player_list, i);
    }
    return 0;
}