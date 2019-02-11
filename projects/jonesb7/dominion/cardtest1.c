/* -----------------------------------------------------------------------
 * This file is for testing the Smithy card from dominion.c
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

	printf ("TESTING Smithy:\n");
	printf("Initializing new game\n");
	initializeGame(NUM_PLAYER, k, SEED, &G);
	const int PLAYER = G.whoseTurn;
	printf("Adding smithy to hand\n");
	int handPos = G.handCount[PLAYER];
	gainCard(smithy, &G, HAND_FLAG, PLAYER);
	int handCount = G.handCount[PLAYER];
	printf("Cards in hand = %d\n", handCount);

	printf("Playing smithy card\n");
	smithyEffect(G.handCount[PLAYER]-1, PLAYER, &G);
	printf("Cards in hand = %d, Expected = %d\n", G.handCount[PLAYER], handCount + 3 - 1);
	if (G.handCount[PLAYER] != handCount + 1) failedTests++;
	printf("Card at handPos %d is: %d, Expected: not %d\n", handPos, G.hand[PLAYER][handPos], smithy);
	if (G.hand[PLAYER][handPos] == smithy) failedTests++;

	if (failedTests == 0) {
		printf("PASSED ALL TESTS!\n");
	} else {
		printf("FAILED %d TESTS!\n", failedTests);
	}

	return 0;
}