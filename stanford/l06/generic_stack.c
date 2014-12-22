/**
 * @file generic_stack.c
 * @author volovo
 * @date 1.12.2041
 * @brief Generic stack implementace
 */

#include "generic_stack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void stack_new(stack *s, int elem_size, void (*freefn)(void *)) {
	assert(elem_size);           // safety first
	s->elem_size = elem_size;
	s->freefn = freefn;
	s->logical_length = 0;
	s->allocated_length = STACK_INIT_SIZE;
	s->elem = malloc(STACK_INIT_SIZE * s->elem_size);
	assert(s->elem != NULL);
	/* malloc velmi vzacne zfailuje pokud dosla pamet,
	 * chyba je vetsinou ve volani... pred tim se zavolalo
	 * free() na neco, co se nemelo 
	 * Obecne v bussiness aplikacich by se kontrola spravnosti
	 * malloc() delat mela... test a pote error + exit.*/
}

void stack_dispose(stack *s) {
	if (s->freefn != NULL) {
		for ( ; s->logical_length > 0; --s->logical_length) {
			s->freefn(((char *)s->elem) + (s->elem_size * s->logical_length));
		}
	}

	free(s->elem);
}

/** 
 * Tohle je priklad pouziti static. Static ma v C/C++ mraky vyznamu, tohle je jeden z nich:
 * - static deklarujici prototyp C nebo C++ funkce
 * - znamena to, ze funkce je privatni a nema byt inzerovana mimo tento soubor
 * - v mnoha ohledech je to podobne jako keyword private v C++
 * - technicky vzato static stanovuje StackGrow pro "internal linkage" - neexportuje se 
 *   v .o souboru, tudiz nelze volat z jineho souboru
 * - funkce bez static jsou globalni - to znamena, ze jsou exportovany v .o souboru
 * Pokud static pouziju u definici C++ metody, tak to znamena, ze metoda neni metoda,
 * ale normalni funkce a je tak zkompilovana. 
 * - static metoda nema k dispozici this pointer 
 * - static metodu lze volat aniz by existovala instance trida, ve ktere metoda je
 */
static void StackGrow(stack *s) {
	s->allocated_length *= 2;
	s->elem = realloc(s->elem, s->allocated_length * s->elem_size);
	assert(s->elem != NULL);
}

/** 
 * C++ nezna nic jako realloc(), takze se musi misto toho naalokovat nove pole
 * prekopirovat obsah a uvolnit stare pole. 
 * realloc() zkusi zvetsit pamet na miste v heapu, kde se nachazi. Lze pouze
 * pokud v heapu pamet za pointerem je volna. Pokud to nejde hleda jine misto a
 * pote tam nakopiruje puvodni. => realloc je efektivnejsi nez free+malloc.
 * Kdyz realloc dostane NULL jako prvni parametru funguje jako malloc. */ 
void stack_push(stack *s, void *elem_addr) {
	if (s->logical_length == s->allocated_length) {
		StackGrow(s);
	}
	/* V nasledujicim copy funkci musim pretypovat s->elem na (char*) jinak 
	   kompilator by mohle delat blbe pointer aritmetiku... a kvuli citelnosti */
	memcpy(((char *)s->elem) + (s->logical_length * s->elem_size), elem_addr, s->elem_size); 
	s->logical_length++;
}

/**
 * Duvod proc se element nevraci return kodem ale pres parametr je ten,
 * ze nechci, aby ten kdo vola stack funkce byl zodpovedny za uvolnovani
 * pameti, ktera byla naalokovana uvnitr stack funkci. A kdybych chtel vysledek
 * vracet v return hodnote (void *), tak bych tady musel dynamicky naalokovat misto 
 * o velikosti s->elem_size, kdyz dostanu adresu prvku v parametru nic alokovat nemusim. */
void stack_pop(stack *s, void *elem_addr) {
	assert(s->logical_length > 0);
	/* opet musim udelat pretypovani na (char*) kvuli pointer aritmetice */
	s->logical_length--;
	memcpy(elem_addr, ((char *)s->elem) + (s->logical_length * s->elem_size), s->elem_size);
}

