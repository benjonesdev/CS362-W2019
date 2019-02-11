/* -----------------------------------------------------------------------
 * This file is for testing the isGameOver function from dominion.c
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
	const int IS_NOT_GAME_OVER = 0;
	const int IS_GAME_OVER  = 1;

	int k[10] = {adventurer, council_room, feast, gardens, mine, 
    			 	   remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int failedTests = 0;

	printf ("TESTING isGameOver():\n");
	printf("Initializing new game\n");
	initializeGame(NUM_PLAYER, k, SEED, &G);
	printf("isGameOver(&G) = %d, Expected = %d\n", isGameOver(&G), IS_NOT_GAME_OVER);
	if (isGameOver(&G) != IS_NOT_GAME_OVER) failedTests++;
	// Test Province win condition
	printf("Setting supplyCount of province to 0\n");
	G.supplyCount[province] = 0;
	printf("isGameOver(&G) = %d, Expected = %d\n", isGameOver(&G), 1);
	if (isGameOver(&G) != IS_GAME_OVER) failedTests++;
	printf("Setting supplyCount of province to 1\n");
	G.supplyCount[province] = 1;
	// Test 1 supply pile empty
	printf("Setting supplyCount of smithy to 0\n");
	G.supplyCount[smithy] = 0;
	printf("isGameOver(&G) = %d, Expected = %d\n", isGameOver(&G), IS_NOT_GAME_OVER);
	if (isGameOver(&G) != IS_NOT_GAME_OVER) failedTests++;
	// Test 2 supply piles empty
	printf("Setting supplyCount of adventurer to 0\n");
	G.supplyCount[adventurer] = 0;
	printf("isGameOver(&G) = %d, Expected = %d\n", isGameOver(&G), IS_NOT_GAME_OVER);
	if (isGameOver(&G) != IS_NOT_GAME_OVER) failedTests++;
	// Test 3 supply piles empty
	printf("Setting supplyCount of village to 0\n");
	G.supplyCount[village] = 0;
	printf("isGameOver(&G) = %d, Expected = %d\n", isGameOver(&G), IS_GAME_OVER);
	if (isGameOver(&G) != IS_GAME_OVER) failedTests++;
	if (failedTests == 0) {
		printf("ALL TESTS PASSED!\n");
	} else {
		printf("FAILED %d test(s)\n", failedTests);
	}
	return 0;
}