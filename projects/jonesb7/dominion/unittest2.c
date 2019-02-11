/* -----------------------------------------------------------------------
 * This file is for testing the gainCard function from dominion.c
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
	const int DISCARD_FLAG = 0;
	const int DECK_FLAG = 1;
	const int HAND_FLAG = 2;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, 
    			 	   remodel, smithy, village, baron, great_hall};
	int currentCard;
    struct gameState G;

    printf ("TESTING gainCard():\n");

    initializeGame(numPlayer, k, SEED, &G);
    int discardCount = G.discardCount[PLAYER];
    int deckCount = G.deckCount[PLAYER];
    int handCount = G.handCount[PLAYER];
    for (currentCard = 0; currentCard <= treasure_map; currentCard++) {
    	int supplyCount = G.supplyCount[currentCard];
    	// Card in game
    	if (currentCard <= great_hall) {
    		// Discard card
    		printf("Discarding card %d\n", currentCard);
    		gainCard(currentCard, &G, DISCARD_FLAG, PLAYER);
    		printf("\tG.discardCount = %d, Expected = %d\n",
    				G.discardCount[0], ++discardCount);
    		printf("\tG.supplyCount[%d] = %d, Expected = %d\n",
    				currentCard, G.supplyCount[currentCard], --supplyCount);
    		printf("\tLast card in player\'s discard = %d, Expected = %d\n", 
    			   G.discard[PLAYER][G.discardCount[PLAYER]-1], currentCard);
    		// Add to deck
    		printf("Adding card %d to deck\n", currentCard);
    		gainCard(currentCard, &G, DECK_FLAG, PLAYER);
    		printf("\tG.deckCount = %d, Expected = %d\n",
    				G.deckCount[0], ++deckCount);
    		printf("\tG.supplyCount[%d] = %d, Expected = %d\n",
    				currentCard, G.supplyCount[currentCard], --supplyCount);
    		printf("\tLast card in player\'s deck = %d, Expected = %d\n", 
    			   G.deck[PLAYER][G.deckCount[PLAYER]-1], currentCard);
    		// Add to hand
    		printf("Adding card %d to hand\n", currentCard);
    		gainCard(currentCard, &G, HAND_FLAG, PLAYER);
    		printf("\tG.handCount = %d, Expected = %d\n",
    				G.handCount[0], ++handCount);
    		printf("\tG.supplyCount[%d] = %d, Expected = %d\n",
    				currentCard, G.supplyCount[currentCard], --supplyCount);
    		printf("\tLast card in player\'s hand = %d, Expected = %d\n", 
    			   G.hand[PLAYER][G.handCount[PLAYER]-1], currentCard);

    		// Supply pile empty
    		G.supplyCount[currentCard] = 0;
    		printf("Setting supplyCount to 0\n");
    		printf("\tgainCard(%d, &G, 0, 0) = %d, Expected = %d\n\n", 
    				currentCard, gainCard(currentCard, &G, 0, 0), -1);
    	// Card not in game
    	} else {
    		printf("Testing card %d that is not in this game\n", currentCard);
    		printf("\tgainCard(%d, &G, 0, 0) = %d, Expected = %d\n\n", 
    				currentCard, gainCard(currentCard, &G, 0, 0), -1);
    	}
    }

	printf("ALL TESTS PASSED\n");
	return 0;
}