/* -----------------------------------------------------------------------
 * This file is for testing the discardCard function from dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int main() {
	const int SEED = 1000;
	const int numPlayer = 2;
	const int PLAYER = 0;
	const int PLAYED_FLAG = 0;
	const int TRASH_FLAG = 1;
	const int HAND_SIZE = 4;

	int k[10] = {adventurer, council_room, feast, gardens, mine, 
    			 	   remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING discardCard():\n");

    initializeGame(numPlayer, k, SEED, &G);
    memset(G.hand[PLAYER], -1, MAX_HAND);
    G.handCount[PLAYER] = HAND_SIZE;
    // Trash a card
    int playedCardCount = G.playedCardCount;
    int handCount = G.handCount[PLAYER];
    printf("Trashing the card at position 3 in player 0\'s hand\n");
	discardCard(3, PLAYER, &G, TRASH_FLAG);
	printf("\tG.playedCardCount = %d, Expected = %d\n", G.playedCardCount, playedCardCount);
	printf("\tG.handCount[0] = %d, Expected = %d\n", G.handCount[PLAYER], --handCount);
 	// Play middle card at position 1
 	printf("Playing the middle card at position 1 in player 0\'s hand\n");
	discardCard(1, PLAYER, &G, PLAYED_FLAG);
	printf("\tG.playedCardCount = %d, Expected = %d\n", G.playedCardCount, ++playedCardCount);
	printf("\tG.handCount[0] = %d, Expected = %d\n", G.handCount[PLAYER], --handCount);
	printf("\tG.hand[0][1] = %d, Expected = %d\n", G.hand[PLAYER][1], -1);
	// Play last card at position 1
	printf("Playing the last card at position 1 in player 0\'s hand\n");
	discardCard(1, PLAYER, &G, PLAYED_FLAG);
	printf("\tG.playedCardCount = %d, Expected = %d\n", G.playedCardCount, ++playedCardCount);
	printf("\tG.handCount[0] = %d, Expected = %d\n", G.handCount[PLAYER], --handCount);
	// Play only card in hand
	printf("Playing the only card in player 0\'s hand\n");
	discardCard(0, PLAYER, &G, PLAYED_FLAG);
	printf("\tG.playedCardCount = %d, Expected = %d\n", G.playedCardCount, ++playedCardCount);
	printf("\tG.handCount[0] = %d, Expected = %d\n", G.handCount[PLAYER], --handCount);
	return 0;
}