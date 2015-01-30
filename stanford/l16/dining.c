/**
 * @file dining.c
 * @author volovo
 * @date 29.01.2015
 * @brief Multithreading sample.
 * @detail Dining philosophers synchronization + deadlock 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

/* nasledujici error handling se hodi i pro jine funkce:
 * handle_error(msg) napr. pro strdup, malloc, a jine, ktere
 * nevraceji error number. */
#define handle_error_en(en, msg) \
          do { errno = en; perror(msg); exit(EXIT_FAILURE); } while(0)

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while(0)

#define PHILOSOPHERS_COUNT 5
#define DAILY_CYCLE 20
     
void *philosopher(void *arg);
void think(int id);
void eat(int id);

sem_t forks[PHILOSOPHERS_COUNT];    /**< semafory na synchronizaci vidlicek */
sem_t num_allowed_to_eat;           /**< semafory na pro prevenci deadlocku */

/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	pthread_t philosophers[PHILOSOPHERS_COUNT];
	int ids[PHILOSOPHERS_COUNT];
	int rc;
	void *res;
	int i;
	
	for (i = 0; i < PHILOSOPHERS_COUNT; i++) {
		rc = sem_init(&forks[i], 0, 1);                                       
		if (rc != 0) handle_error_en(rc, "sem_init");      
	}

	/* zarucim, aby aspon jeden filosof mohl jist */
	rc = sem_init(&num_allowed_to_eat, 0, PHILOSOPHERS_COUNT - 1);                                       
	if (rc != 0) handle_error_en(rc, "sem_init");      

	/* nastartuj filosofy */
	for (i = 0; i < PHILOSOPHERS_COUNT; i++) {
		ids[i] = i;
		rc = pthread_create(&philosophers[i], NULL, &philosopher, &ids[i]);
		if (rc != 0) handle_error_en(rc, "pthread_create");
	}

	/* posbirej thready */
	for (i = 0; i < PHILOSOPHERS_COUNT; i++) {
		rc = pthread_join(philosophers[i], &res);
		if (rc != 0) handle_error_en(rc, "pthread_join");
	}

	/* hotovo */
	for (i = 0; i < PHILOSOPHERS_COUNT; i++) {
		rc = sem_destroy(&forks[i]);
		if (rc != 0) handle_error_en(rc, "sem_destroy");
	}
	rc = sem_destroy(&num_allowed_to_eat);                                       
	if (rc != 0) handle_error_en(rc, "sem_destroy");      


	return 0; 
}

void *philosopher(void *arg) {
	int *id = (int *)arg;
	int i;

	for (i = 0; i < DAILY_CYCLE; i++) {
		think(*id);

		sem_wait(&num_allowed_to_eat); 
		sem_wait(&forks[*id]); 
		sem_wait(&forks[(*id + 1) % PHILOSOPHERS_COUNT]); 
		eat(*id);
		sem_post(&forks[*id]); 
		sem_post(&forks[(*id + 1) % PHILOSOPHERS_COUNT]); 
		sem_post(&num_allowed_to_eat); 
	}
	return NULL;
}


void think(int id) {
	printf("Cislo %d spi.\n", id);
	sleep(1);
}

void eat(int id) {
	printf("Cislo %d zere.\n", id);
	//sleep(1);
}


