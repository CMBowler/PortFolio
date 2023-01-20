#ifndef ODDS_FILE
#define ODDS_FILE

#include "Sets.h"

double find_odds(player * P, int player);
int load_counts(int num[], char suit[], player * P, int player);
int suit_index(char suit);
double flush_odds(int suit[]);

#endif