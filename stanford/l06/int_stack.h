/**
 * @file int_stack.h
 * @author volovo
 * @date 1.12.2041
 * @brief integer stack header
 */

#ifndef INT_STACK_H
#define INT_STACK_H

#ifndef STACK_INIT_SIZE
#define STACK_INIT_SIZE 4
#endif

/**
 * Type int_struct
 * ---------------
 * Zasobnik, ktery podporuje pouze inty.
 */
typedef struct {
	int *elem;
	int logical_length;
	int allocated_length;
} int_stack;

/**
 * Function int_stack_new
 * ----------------------
 * @param s - stack address
 * Inicializuje stack, alokuje pamet pro STACK_INT_SIZE prvku.
 */
void int_stack_new(int_stack *s);

/**
 * Function int_stack_dispose
 * --------------------------
 * @param s - stack address
 * Zrusi stack, odalokuje pamet.
 */
void int_stack_dispose(int_stack *s);

/**
 * Function int_stack_push
 * -----------------------
 * @param s - stack address
 * @param value - novy prvek
 * Vlozi int do stacku, pokud je potreba, tak prialokuje pamet.
 */
void int_stack_push(int_stack *s, int value);

/**
 * Function int_stack_pop
 * ----------------------
 * @param s - stack address
 * Vybere prvek ze zasobniku a vrati ho.
 */
int int_stack_pop(int_stack *s);

/**
 * Function int_stack_print
 * ------------------------
 * @param s - stack address
 * Vytiskne obsah zasobniku na obrazovku.
 */
void int_stack_print(int_stack *s);


#endif  /* INT_STACK_H */
