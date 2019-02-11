/* -----------------------------------------------------------------------
 * This file is for testing the Adventurer card from dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int isTreasureCard(int card) {
	return card >= copper && card <= gold;
}

int main() {
	const int SEED = 1000;
	const int NUM_PLAYER = 2;
	const int HAND_FLAG = 2;

	int k[10] = {adventurer, council_room, feast, gardens, mine, 
    			 	   remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int temphand[MAX_HAND];
    int failedTests = 0;
    int i;

	printf ("TESTING adventurer:\n");
	printf("Initializing new game\n");
	initializeGame(NUM_PLAYER, k, SEED, &G);
	const int PLAYER = G.whoseTurn;
	printf("Adding Adventurer to hand\n");
	int handCount = G.handCount[PLAYER];
	gainCard(adventurer, &G, HAND_FLAG, PLAYER);

	printf("Cards in hand = %d\n", handCount + 1);
	printf("Playing adventurer card\n");
	adventurerEffect(PLAYER, &G, 0, temphand, 0);
	printf("Cards in hand = %d, Expected = %d\n", G.handCount[PLAYER], handCount+2);
	if (G.handCount[PLAYER] != handCount+2) failedTests++;
	printf("Last card in hand is a treasure card = %d, Expected = %d\n", 
		   isTreasureCard(G.hand[PLAYER][G.handCount[PLAYER]-1]), 1);
	if (isTreasureCard(G.hand[PLAYER][G.handCount[PLAYER]-1]) != 1) failedTests++;
	printf("Second to last card in hand is a treasure card = %d, Expected = %d\n", 
		   isTreasureCard(G.hand[PLAYER][G.handCount[PLAYER]-2]), 1);
	if (G.hand[PLAYER][G.handCount[PLAYER]-2] != 1) failedTests++;
	for (i = 0; i < G.discardCount[PLAYER]; i++) {
		printf("Card %d in discard is a treasure card = %d, Expected = %d\n",
			   i, isTreasureCard(G.discard[PLAYER][i]), 0);
	}

	if (failedTests == 0) {
		printf("PASSED ALL TESTS!\n");
	} else {
		printf("FAILED %d TESTS!\n", failedTests);
	}

	return 0;
}