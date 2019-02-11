/* -----------------------------------------------------------------------
 * This file is for testing the Great Hall card from dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int main() {
	const int SEED = 1000;
	const int NUM_PLAYER = 2;
	const int HAND_FLAG = 2;

	int k[10] = {adventurer, council_room, feast, gardens, mine, 
    			 	   remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int failedTests = 0;

	printf ("TESTING great hall:\n");
	printf("Initializing new game\n");
	initializeGame(NUM_PLAYER, k, SEED, &G);
	const int PLAYER = G.whoseTurn;
	printf("Adding great hall to hand\n");
	gainCard(great_hall, &G, HAND_FLAG, PLAYER);
	int handPos = G.handCount[PLAYER]-1;
	int handCountBefore = G.handCount[PLAYER];
	int numActionsBefore = G.numActions;

	printf("Playing great hall card\n");
	greathallEffect(handPos, PLAYER, &G);
	// Check card was drawn
	printf("Cards in hand = %d, Expected = %d\n", G.handCount[PLAYER], handCountBefore);
	if (G.handCount[PLAYER] != handCountBefore) failedTests++;
	// Check action was added
	printf("G.numActions = %d, Expected = %d\n", G.numActions, numActionsBefore + 1);
	if (G.numActions != numActionsBefore + 1) failedTests++;
	// Check card was added to played pile
	printf("G.playedCardCount = %d, Expected = %d\n", 
		   G.playedCardCount, 1);
	if (G.playedCardCount != 1) failedTests++;

	if (failedTests == 0) {
		printf("PASSED ALL TESTS!\n");
	} else {
		printf("FAILED %d TESTS!\n", failedTests);
	}

	return 0;
}