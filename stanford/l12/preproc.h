/**
 * @file preproc.h
 * @author volovo
 * @date 22.12.2014
 * @brief sample for preprocessor directiv
 * @detail
 * .h soubory neobsahuji zadny kod, pouze prototypy a #definy
 * Je rozdil mezi deklarovanim protypu funkce (dela se v .h souborech)
 * a definovanim funkce (.c soubory - obsahuje kod)
 */

#ifndef PREPROC_H    // tohle delam, aby nedoslo k nekonecne rekurzi pri includovani,
#define PREPROC_H    // dnesni kompilatory nekonecnou rekurzi vetsinou nedopusti...

/* Tohle je dobry priklad pro assignment 3 nebo na priklady v l06, l07.
   Je to lepsi nez to copy pastovat pokazde, kdyz to potrebuju.  */
#define NthElemAddr(base, elem_size, index) \
        ((char *) base + index*elem_size)


/* Ukazka assert(), takhle nejak vypada v assert.h */
#ifdef NDEBUG
  #define assert(cond) (void) 0
#else
  #define assert(cond) \
        (cond) ? ((void) 0) : fprintf(stderr, "Je to v hajzlu.\n"); exit(0)
#endif


/* spatny priklad #define */
#define MAX(a,b) (((a) > (b)) ? (a) : (b))    // zavorkovani delam kvuli bezpecnosti
/* kdyz udelam:
 * int max = MAX(fibonacci(100), factorial(4000));
 * vyevaluuje se to jako: 
 * int max = (fib(100) > fact(4000)) ? fib(100) : fact(4000);
 * takze ta vetsi funkce se provede dvakrat, coz je neefektivni 
 * anebo se muze udelat taky tohle:
 * int max = MAX(m++, n++);   coz je blbost
 */


#endif  /* PREPROC_H */
