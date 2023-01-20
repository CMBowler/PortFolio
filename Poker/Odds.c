#include "Odds.h"

int num_count[14]; // 0->1, 14->A
int suit_count[4];

double find_odds(player * P, int player){
    int total = load_counts(num_count, suit_count, P, player);
    float flush = flush_odds(suit_count);
}
// loads counts of numbers and suits into arrays, and returns total num of cards..
int load_counts(int num[], char suit[], player * P, int player){
    card * hand_card = (P + player)->hand;
    int total;
    //load all cards into array
    int j = 0;
    char suit;
    while(hand_card){
        num_count[hand_card->num]++;
        suit_count[suit_index(hand_card->suit)]++;
        hand_card = hand_card->next;
        total++;
    }
    hand_card = P->hand;
    while(hand_card){
        num_count[hand_card->num]++;
        suit_count[suit_index(hand_card->suit)]++;
        hand_card = hand_card->next;
        total++;
    }
    return total;
}

int suit_index(char suit){
    switch (suit)
    {
    case 'H':
        return 0;
        break;
    case 'D':
        return 1;
        break;
    case 'S':
        return 2;
        break;
    case 'C':
        return 3;
        break;
    default:
        break;
    }
}

double flush_odds(int suit[]){
    int a = highest_suit(suit);
}


