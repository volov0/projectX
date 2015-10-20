/**
 * @file generic_queue.c
 * @author volovo
 * @brief Generic queue implementace
 */

#include "generic_queue.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void queue_new(queue *q, int elem_size, void (*freefn)(void *)) {
	assert(elem_size);           // safety first
	q->elem_size = elem_size;
	q->freefn = freefn;
	q->logical_length = 0;
	q->allocated_length = QUEUE_INIT_SIZE;
	q->elem = malloc(QUEUE_INIT_SIZE * q->elem_size);
	assert(q->elem != NULL);
	/* malloc velmi vzacne zfailuje pokud dosla pamet,
	 * chyba je vetsinou ve volani... pred tim se zavolalo
	 * free() na neco, co se nemelo 
	 * Obecne v bussiness aplikacich by se kontrola spravnosti
	 * malloc() delat mela... test a pote error + exit.*/
}

void queue_dispose(queue *q) {
	if (q->freefn != NULL) {
		for ( ; q->logical_length > 0; --q->logical_length) {
			q->freefn(((char *)q->elem) + (q->elem_size * ((q->logical_length + q->front) % q->allocated_length)));
		}
	}

	free(q->elem);
}

void QueueGrow(queue *q) {
	void *old_elem = q->elem;
	q->elem = malloc(q->allocated_length * 2 * q->elem_size);
	assert(q->elem != NULL);
	memcpy(q->elem, (char *)old_elem + (q->front * q->elem_size), q->elem_size *(MIN(q->allocated_length - q->front, q->logical_length)));
	if (q->logical_length > q->allocated_length - q->front) {
		memcpy((char *)q->elem + q->elem_size *(q->allocated_length - q->front), old_elem, q->logical_length - (q->allocated_length - q->front)); 
	}
	q->allocated_length *= 2;
	free(old_elem);
}

void queue_push(queue *q, void *elem_addr) {
	if (q->logical_length == q->allocated_length) {
		QueueGrow(q);
	}
	/* V nasledujicim copy funkci musim pretypovat s->elem na (char*) jinak 
	   kompilator by mohle delat blbe pointer aritmetiku... a kvuli citelnosti */
	memcpy(((char *)q->elem) + q->elem_size * ((q->logical_length + q->front) % q->allocated_length), elem_addr, q->elem_size); 
	q->logical_length++;
}

void queue_pop(queue *q, void *elem_addr) {
	assert(q->logical_length > 0);
	/* opet musim udelat pretypovani na (char*) kvuli pointer aritmetice */
	q->logical_length--;
	memcpy(elem_addr, ((char *)q->elem) + q->elem_size * ((q->logical_length + q->front) & q->allocated_length), q->elem_size);
}

