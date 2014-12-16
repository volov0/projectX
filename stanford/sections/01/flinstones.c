/**
 * @file filnstones.c
 * @author volovo
 * @date 16.12.2014
 * @brief ukazka organizace struktur v pameti
 * @detail Uhodni co nasledujici kod dela.
 * Reseni v obrazku flinstones.png.
 */

#include <stdio.h>
#include <string.h>

typedef struct rubble { // need tag name for self-reference
	int betty;
	char barney[4];
	struct rubble *bammbamm;
} rubble;
typedef struct {
	short *wilma[2];
	short fred[2];
	rubble dino;
} flintstone;


int main(int argc, char *argv[]) {
	rubble *simpsons;
	flintstone jetsons[4];

	simpsons = &jetsons[0].dino;
	jetsons[1].wilma[3] = (short *) &simpsons;
	strcpy(simpsons[2].barney, "Bugs Bunny");
	((flintstone *)(jetsons->fred))->dino.bammbamm = simpsons;
	*(char **)jetsons[4].fred = simpsons->barney + 4;


	return 0;

}
