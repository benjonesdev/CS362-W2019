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
int checkSmithyCard(int handPos, int currentPlayer, struct gameState *post) {
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	int r = smithyEffect(handPos, currentPlayer, post);

	// Smithy should draw 3 cards then be discarded from hand
	drawCard(currentPlayer, &pre);
	drawCard(currentPlayer, &pre);
	drawCard(currentPlayer, &pre);
	discardCard(handPos, currentPlayer, &pre, 0);

	// Return 1 if gamestate reflects expected behavior, else return 0
	if (r != 0 || memcmp(&pre, post, sizeof(struct gameState)) != 0) {
		return 1;
	} else {
		return 0;
	}
}

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

	printf("Testing smithyEffect\n");
	for (i = 0; i < NUM_TESTS; i++) {
	    randomizeGameState(&state);

	    int currentPlayer = state.whoseTurn;
	    int handPos = floor(Random() * state.handCount[currentPlayer]);

	    if (checkSmithyCard(handPos, currentPlayer, &state) != 0) {
	    	printf("Test case %d failed\n", i+1);
	    } else {
	    	printf("Test case %d passed\n", i+1);
	    }
	}
}
