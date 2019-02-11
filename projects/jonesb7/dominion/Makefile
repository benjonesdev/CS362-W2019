CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

testBuyCard: unittest1.c dominion.o rngs.o
	gcc -o testBuyCard -g unittest1.c dominion.o rngs.o $(CFLAGS)

testGainCard: unittest2.c dominion.o rngs.o
	gcc -o testGainCard -g unittest2.c dominion.o rngs.o $(CFLAGS)

testDiscardCard: unittest3.c dominion.o rngs.o
	gcc -o testDiscardCard -g unittest3.c dominion.o rngs.o $(CFLAGS)

testIsGameOver: unittest4.c dominion.o rngs.o
	gcc -o testIsGameOver -g unittest4.c dominion.o rngs.o $(CFLAGS)

testSmithy: cardtest1.c dominion.o rngs.o
	gcc -o testSmithy -g cardtest1.c dominion.o rngs.o $(CFLAGS)

testAdventurer: cardtest2.c dominion.o rngs.o
	gcc -o testAdventurer -g cardtest2.c dominion.o rngs.o $(CFLAGS)

testGreatHall: cardtest3.c dominion.o rngs.o
	gcc -o testGreatHall -g cardtest3.c dominion.o rngs.o $(CFLAGS)

unittestresults: testGainCard dominion.o
	echo "Result for running unit tests:" > unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	./testBuyCard >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	./testGainCard >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	./testDiscardCard >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "unittest4.c:" >> unittestresults.out
	./testIsGameOver >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "cardtest1.c:" >> unittestresults.out
	./testSmithy >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "cardtest2.c:" >> unittestresults.out
	./testAdventurer >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "cardtest3.c:" >> unittestresults.out
	./testGreatHall >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
