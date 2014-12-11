/**
 * @file qsort.h
 * @author volovo
 * @date 11.12.2014
 * @brief implementace quick sortu
 */

#ifndef QSORT_H
#define QSORT_H

/**
 * Function rotate
 * ---------------
 * @param front - zacatek pole
 * @param middle - ukazetel do pole, ktery urcuje rotovani
 * @param end - ukazatel na konec pole
 * @detail Funkce posune uvodni cast pole (od front az k middle)
 * na konec pole. Tzn cast od middle do end se posune na zacatek
 */
void rotate(void *front, void *middle, void *end);

/**
 * Function qsort
 * --------------
 * @param base - pointer na zacatek pole k sortovani
 * @param size - velikost pole k sortovani
 * @param elem_size - velikost jednoho prvku pole
 * @param cmpfn - porovnavaci funkce dvou prvku
 * @detail - Quick Sort
 */
void mqsort(void *base, int size, int elem_size, int (*cmpfn)(void *, void *));

#endif  /* QSORT_H */
