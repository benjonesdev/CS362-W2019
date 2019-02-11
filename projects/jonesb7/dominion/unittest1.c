/* -----------------------------------------------------------------------
 * This file is for testing the buyCard function from dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {
    const int SEED = 1000;
    const int NUM_PLAYER = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine, 
                       remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int failedTests = 0;


    printf ("TESTING buyCard():\n");
    printf("Initializing new game\n");
    initializeGame(NUM_PLAYER, k, SEED, &G);
    const int PLAYER = G.whoseTurn;
    int handCount = G.handCount[PLAYER];
    int coins = G.coins;
printf("coins: %d\n", coins);
    // No buys left
    printf("Setting G.numBuys to 0\n");
    G.numBuys = 0;
    printf("Try to buy smithy\n");
    buyCard(smithy, &G);
    printf("\tG.handCount[%d] = %d, Expected = %d\n", PLAYER, G.handCount[PLAYER], handCount);
    if (G.handCount[PLAYER] != handCount) failedTests++;
    printf("\tG.coins = %d, Expected = %d\n", G.coins, coins);
    if (G.coins != coins) failedTests++;
    printf("Setting G.numBuys to 1\n");
    G.numBuys = 1;
    // No cards of that type left
    printf("Setting G.supplyCount[smithy] to 0\n");
    G.supplyCount[smithy] = 0;
    printf("Try to buy smithy\n");
    buyCard(smithy, &G);
    printf("\tG.handCount[%d] = %d, Expected = %d\n", PLAYER, G.handCount[PLAYER], handCount);
    if (G.handCount[PLAYER] != handCount) failedTests++;
    printf("\tG.coins = %d, Expected = %d\n", G.coins, coins);
    if (G.coins != coins) failedTests++;
    printf("Setting G.supplyCount[smithy] to 5\n");
    G.supplyCount[smithy] = 5;
    // Not enough money
    printf("Setting G.coins to 0\n");
    G.coins = 0;
    printf("Try to buy smithy\n");
    buyCard(smithy, &G);
    printf("\tG.handCount[%d] = %d, Expected = %d\n", PLAYER, G.handCount[PLAYER], handCount);
    if (G.handCount[PLAYER] != handCount) failedTests++;
    printf("\tG.coins = %d, Expected = %d\n", G.coins, 0);
    if (G.coins != 0) failedTests++;
    printf("Setting G.coins to 4\n");
    G.coins = 4;
    printf("Try to buy smithy\n");
    buyCard(smithy, &G);
    printf("\tG.handCount[%d] = %d, Expected = %d\n", PLAYER, G.handCount[PLAYER], handCount);
    if (G.handCount[PLAYER] != handCount) failedTests++;
    printf("\tG.coins = %d, Expected = %d\n", G.coins, 0);
    if (G.coins != 0) failedTests++;
    printf("\tG.discard[%d][%d] = %d, Expected = %d\n", 
           PLAYER, G.discardCount[PLAYER]-1,  G.discard[PLAYER][G.discardCount[PLAYER]-1], smithy);
    if (G.discard[PLAYER][G.discardCount[PLAYER]-1] != smithy) failedTests++;
    if (failedTests == 0) {
        printf("ALL TESTS PASSED!\n");
    } else {
        printf("FAILED %d TESTS\n", failedTests);
    }

    return 0;
}