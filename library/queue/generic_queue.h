/**
 * @file generic_queue.h
 * @author volovo
 * @date 1.12.2041
 * @brief generic queue header
 */

#ifndef GENERIC_QUEUE_H
#define GENERIC_QUEUE_H

#ifndef QUEUE_INIT_SIZE
#define QUEUE_INIT_SIZE 4
#endif

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

/**
 * Type queue
 * ---------------
 * Genericka fronta.
 */
typedef struct {
	void *elem;
	int  front;
	int  elem_size;
	int  logical_length;
	int  allocated_length;
	void (*freefn)(void *);
} queue;

/**
 * Function queue_new
 * ------------------
 * @param q - queue address
 * @param elem_size - velikost jednoho prvku
 * @param freefn - funkce k uvolneni pameti pro elementy, muze byt NULL,
 *   pouzije se pri queue_dispose k uvolneni zbylych elementu  
 * @detail Inicializuje frontu, alokuje pamet pro QUEUE_INT_SIZE prvku.
 */
void queue_new(queue *q, int elem_size, void (*freefn)(void *));

/**
 * Function queue_dispose
 * ----------------------
 * @param s - queue address
 * @detail Zrusi frontu, odalokuje pamet.
 */
void queue_dispose(queue *q);

/**
 * Function queue_push
 * -------------------
 * @param q - queue address
 * @elem_addr - novy prvek
 * @detail Vlozi prvek do fronty, pokud je potreba, tak prialokuje pamet.
 */
void queue_push(queue *q, void *elem_addr);

/**
 * Function queue_pop
 * ------------------
 * @param q - queue address
 * @elem_addr - adresa prvku, kde se vrati nejstarsi prvek z fronty
 * @detail Vybere prvek z fronty a vrati ho.
 */
void stack_pop(queue *q, void *elem_addr);


#endif  /* GENERIC_QUEUE_H */
