/**
 * @file threads.c
 * @author volovo
 * @date 27.01.2015
 * @brief Multithreading sample.
 * @detail ... 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

/* nasledujici error handling se hodi i pro jine funkce:
 * handle_error(msg) napr. pro strdup, malloc, a jine, ktere
 * nevraceji error number. */
#define handle_error_en(en, msg) \
          do { errno = en; perror(msg); exit(EXIT_FAILURE); } while(0)

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while(0)
    

typedef struct {
	pthread_t thread_id;       /**< agent thread id            */
	pthread_mutex_t *tmutex;   /**< pointer na shared mutex    */
	int agent_id;              /**< agent id number            */
	int *num_tickets_to_sell;  /**< pointer na shared resource */
	int num_tickets_sold;      /**< jizdenky prodane timto agentem */
} thread_info;

void *sell_tickets(void *arg); 
int random_chance(float p);

/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	pthread_mutex_t tmutex;
	int num_agents = 10;
	thread_info tinfo[10];
	int num_tickets = 150;
	int agent;
	int rc;
	void *res;
	int sum = 0;

	pthread_mutex_init(&tmutex, NULL);
	
	for (agent = 0; agent < num_agents; agent++) {  
		tinfo[agent].tmutex = &tmutex;
		tinfo[agent].agent_id = agent;
		tinfo[agent].num_tickets_to_sell = &num_tickets;
		tinfo[agent].num_tickets_sold = 0;
		rc = pthread_create(&tinfo[agent].thread_id, NULL, &sell_tickets, &tinfo[agent]);
		if (rc != 0) handle_error_en(rc, "pthread_create");
	}
	
	for (agent = 0; agent < num_agents; agent++) {  
		rc = pthread_join(tinfo[agent].thread_id, &res);
		if (rc != 0) handle_error_en(rc, "pthread_join");
		printf("Agent %d konci s rc %d. Prodal %d jizdenek.\n", agent, rc, tinfo[agent].num_tickets_sold);
		sum += tinfo[agent].num_tickets_sold;
	}

	printf("celkem prodano %d jizdenek.\n", sum);
	pthread_mutex_destroy(&tmutex);

	return 0; 
}

void *sell_tickets(void *arg) {
	thread_info *tinfo = (thread_info *)arg;
	while (1) {
		pthread_mutex_lock(tinfo->tmutex);

		if (*(tinfo->num_tickets_to_sell) == 0) break;
		(*(tinfo->num_tickets_to_sell))--;

		printf("Agent %d prodava jizdenku.\n", tinfo->agent_id);
		if (random_chance(0.2)) sleep(1);

		pthread_mutex_unlock(tinfo->tmutex);

		tinfo->num_tickets_sold++;
		if (random_chance(0.2)) sleep(1);
	}
	/* pokud se udela v predchozi smycce break je treba unlock */
	pthread_mutex_unlock(tinfo->tmutex);  

	printf("Agent %d: hotovo.\n", tinfo->agent_id);
	return NULL;
}

int random_chance(float p) {
	return rand() < p * ((float)RAND_MAX + 1);
}
