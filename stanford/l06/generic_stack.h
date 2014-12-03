/**
 * @file generic_stack.h
 * @author volovo
 * @date 1.12.2041
 * @brief generic stack header
 */

#ifndef STACK_H
#define STACK_H

#ifndef STACK_INIT_SIZE
#define STACK_INIT_SIZE 4
#endif

/**
 * Type int_struct
 * ---------------
 * Genericky zasobnik.
 */
typedef struct {
	void **elem;
	int  elem_size;
	int  logical_length;
	int  allocated_length;
	void (*cpyfn)(void *, void *);
} stack;

/**
 * Function stack_new
 * ------------------
 * @param s - stack address
 * @param elem_size - velikost jednoho prvku
 * Inicializuje stack, alokuje pamet pro STACK_INT_SIZE prvku.
 */
void stack_new(stack *s, int elem_size, void (*cpyfn)(void *, void *));

/**
 * Function stack_dispose
 * ----------------------
 * @param s - stack address
 * Zrusi stack, odalokuje pamet.
 */
void stack_dispose(stack *s);

/**
 * Function stack_push
 * -------------------
 * @param s - stack address
 * @param value - novy prvek
 * Vlozi int do stacku, pokud je potreba, tak prialokuje pamet.
 */
void stack_push(stack *s, void *value);

/**
 * Function stack_pop
 * ------------------
 * @param s - stack address
 * Vybere prvek ze zasobniku a vrati ho.
 */
void *stack_pop(stack *s);


#endif  /* STACK_H */
