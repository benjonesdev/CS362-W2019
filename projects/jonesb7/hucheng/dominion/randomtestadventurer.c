#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

const int NUM_TESTS = 1000;

// Returns 0 if smithy card behaves correctly, else returns 1
int checkAdventurerCard(int handPos, int currentPlayer, struct gameState *post) {
	int cardDrawn;
	int drawntreasure = 0;
	int temphand[MAX_HAND];
	int temphandCount = 0;
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	int r = adventureCardEffect(post, currentPlayer);

	// Adventurer should draw cards until 2 treasure cards are drawn, 
	// Then the non-treasure cards and adventurer will then be discarded
	while(drawntreasure < 2) {
		if (pre.deckCount[currentPlayer] < 1) {
			//if the deck is empty we need to shuffle discard and add to deck
		   	shuffle(currentPlayer, &pre);
		}
		drawCard(currentPlayer, &pre);
		//top card of hand is most recently drawn card.
	    cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer]-1];
	    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
	      	drawntreasure++;
	    } else {
		    temphand[temphandCount] = cardDrawn;
		    pre.handCount[currentPlayer]--; // remove the top card
		    temphandCount++;
		}
	}
	while(temphandCount-1 >= 0) {
		// discard all cards in play that have been drawn
	   	pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[temphandCount-1]; 
	   	temphandCount=temphandCount-1;
	}
	// Remove card from hand
	discardCard(handPos, currentPlayer, &pre, 0);

	// Return 1 if gamestate reflects expected behavior, else return 0
	if (r != 0 || memcmp(&pre, post, sizeof(struct gameState)) != 0) {
		return 1;
	} else {
		return 0;
	}
}

// Creates a 
void randomizeGameState(struct gameState *state) {
	int i;
	int seed = time(NULL);
	int numPlayers = 2 + rand() % 3; 	// random players 2 to 4
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				  remodel, smithy, village, baron, great_hall };
    srand(time(NULL));
	initializeGame(numPlayers, k, seed, state);
	state->whoseTurn = rand() % state->numPlayers;
	// Randomize hand
	state->handCount[state->whoseTurn] = rand() % MAX_HAND;
	for (i = 0; i < state->handCount[state->whoseTurn]; i++) {
		state->hand[state->whoseTurn][i] = rand() % (great_hall + 1);
	}
	// Randomize deck
	state->deckCount[state->whoseTurn] = rand() % (MAX_HAND - state->handCount[state->whoseTurn]);
	for (i = 0; i < state->deckCount[state->whoseTurn]; i++) {
		state->deck[state->whoseTurn][i] = rand() % (great_hall + 1);
	}
	// Randomize discard
	state->discardCount[state->whoseTurn] = 
		rand() % (MAX_HAND - state->handCount[state->whoseTurn] - state->deckCount[state->whoseTurn]);
	for (i = 0; i < state->discardCount[state->whoseTurn]; i++) {
		state->discard[state->whoseTurn][i] = rand() % (great_hall + 1);
	}
}

int main() {
	int i;
	struct gameState state;

	printf("Testing adventurerEffect\n");
	for (i = 0; i < NUM_TESTS; i++) {
	    randomizeGameState(&state);

	    int currentPlayer = state.whoseTurn;
	    int handPos = floor(Random() * state.handCount[currentPlayer]);

	    if (checkAdventurerCard(handPos, currentPlayer, &state) != 0) {
	    	printf("Test case %d failed\n", i+1);
	    } else {
	    	printf("Test case %d passed\n", i+1);
	    }
	}
}
