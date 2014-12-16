/**
 * @file qsort.h
 * @author volovo
 * @date 11.12.2014
 * @brief implementace quick sortu
 */

#ifndef QSORT_H
#define QSORT_H

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
