#include <stdlib.h>
#include <stdio.h>

#include "Sets.h"

// checks hand of player to see if any sets are made,
// returns highest value set
int check_hand(player * P, int player){
    int result = 0;
    int cards_nums[7] = {0};
    char cards_suit[7] = {0};

    load_cards(P, player, cards_nums, cards_suit);

    if(two_kind(cards_nums)){ 
        result = 1;
        if(two_pair(cards_nums)) result = 2;
        if(three_kind(cards_nums)) result = 3;
        if(full_house(cards_nums)) result = 6;
        if(four_kind(cards_nums)) result = 7;
    }
    if(straight(cards_nums)) result = 4;
    if(flush(cards_suit)) result = 5;
    if(straight_flush(cards_nums, cards_suit)) result = 8;
    if(royal_flush(cards_nums, cards_suit)) result = 9;

    print_result(result, player);
    return result;
}

void load_cards(player * P, int player, int cards_nums[], char cards_suit[]){
    card * hand_card = (P + player)->hand;
    //load all cards into array
    int j = 0;
    while(hand_card){
        cards_nums[j] = hand_card->num;
        cards_suit[j] = hand_card->suit;
        hand_card = hand_card->next;
        j++;
    }
    hand_card = P->hand;
    while(hand_card){
        cards_nums[j] = hand_card->num;
        cards_suit[j] = hand_card->suit;
        hand_card = hand_card->next;
        j++;
    }
}

void insertion_sort(int arr[], int size) {
    int temp, index;
    for(int i=1; i<size; i++){
        index = i-1;
        temp = arr[i];
        if(arr[index] > temp){
            while(arr[index] > temp && index >= 0){
                arr[index + 1] = arr[index];
                index--; 
            }
            arr[index + 1] = temp;
        }
    } 
}
// returns value of highest pair, 0 if no pairs
int two_kind(int nums[]){
    int num = 0;    
    for(int i=0; i<7; i++){
        if(nums[i] && nums[i] != num){
            for(int j=0; j<7; j++){
                if(j == i) continue;
                else {
                    if(nums[i] == nums[j]){
                        if(nums[i] > num){
                            num = nums[i];
                        }
                    }
                }
            }
        }
    }
    return num;
}

int two_pair(int nums[]){
    int pair1 = 0, pair2=0;
    for(int i=0; i<7; i++){
        if(nums[i] && nums[i]){
            for(int j=0; j<7; j++){
                if(j == i) continue;
                else {
                    if(nums[i] == nums[j]){
                        if(!pair1) {
                            pair1 = nums[i];
                        } else if(!pair2 && nums[i] != pair1){
                            pair2 = nums[i];
                        }
                    }
                }
            }
        }
    }
    if(pair2){
        return (pair1 > pair2)? pair1:pair2;
    } else return 0;
}

int three_kind(int nums[]){   
    int num = 0;
    int count;
    for(int i=0; i<7; i++){
        count = 1;
        if(nums[i] && nums[i] != num){
            for(int j=0; j<7; j++){
                if(j == i) continue;
                else {
                    if(nums[i] == nums[j]){
                        count++;
                        if(count == 3 && nums[i] > num){
                            num = nums[i];
                        }
                    }
                }
            }
        }
    }
    return num;
}

int four_kind(int nums[]){
    int num = 0;
    int count;
    for(int i=0; i<7; i++){
        count = 1;
        if(nums[i] != 0 && nums[i] != num){
            for(int j=0; j<7; j++){
                if(j == i) continue;
                else {
                    if(nums[i] == nums[j]){
                        count++;
                        if(count == 4 && nums[i] > num){
                            num = nums[i];
                        }
                    }
                }
            }
        }
    }
    return num;
}

int straight(int nums[]){
    insertion_sort(nums, 7);
    int count = 0, i = 1;
    while(nums[i] != 0 && i<7){
        if((nums[i] - nums[i-1]) == 1){
            count++;
            if(count == 4) return nums[i];
        } else if(nums[i+1] - nums[i] > 1){
            count = 0;
        }
        i++;
    } return 0;
}

int flush(char suits[]){
    int count;
    for(int i = 0; i<7; i++){
        count = 1;
        for(int j=0; j<7; j++){
            if(j == i) continue;
            if(suits[j] == suits[i]){
                count++;
                if(count == 5) return 1;
            }
        }
    }
    return 0;
}

int full_house(int nums[]){
    int triple = three_kind(nums);
    int num = 0;
    if(triple){
        for(int i=0; i<7; i++){
            if(nums[i] && nums[i] != triple){
                for(int j=0; j<7; j++){
                    if(j == i) continue;
                    else {
                        if(nums[i] == nums[j]){
                            num = nums[i];
                        }
                    }
                }
            }
        }
    }
    return num;
}

int straight_flush(int nums[], char suits[]){
    return 0;
}

int royal_flush(int nums[], char suits[]){
    return 0;
}

void print_result(int i, int player){
    switch (i)
    {
    case 0:
        printf("Player %i: High Card\n", player);
        break;
    case 1:
        printf("Player %i: Pair\n", player);
        break;
    case 2:
        printf("Player %i: Two Pairs\n", player);
        break;
    case 3: 
        printf("Player %i: Three of a kind\n", player);
        break;
    case 4:
        printf("Player %i: Straight\n", player);
        break;
    case 5:
        printf("Player %i: Flush\n", player);
        break;
    case 6:
        printf("Player %i: Full House\n", player);
        break;
    case 7:
        printf("Player %i: Four of a Kind\n", player);
        break;
    case 8:
        printf("Player %i: Straight Flush\n", player);
        break;
    case 9:
        printf("Player %i: Royal Flush\n", player);
        break;
    default:
        break;
    }
}