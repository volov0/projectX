/**
 * @file prodcons.c
 * @author volovo
 * @date 29.01.2015
 * @brief Multithreading sample.
 * @detail Producer consumer synchronization 
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
    
void *writer(void *arg);
void *reader(void *arg);

char buffer[8];   /**< global promenna, ktera se synchronizuje */
sem_t empty_buffers;  /**< globalni semafor - lepsi by bylo mit ho lokalne a predavat pointer 
                                            - obsahuje pocet mist v bufferu, ktere jsou k dispozici 
											  pro zapis */
sem_t full_buffers;   /**< globalni semafor - lepsi by bylo mit ho lokalne a predavat pointer 
                                            - obsahuje pocet mist v bufferu, na kterych neco je
											  a tudiz se muzou cist */

/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	pthread_t twriter;
	pthread_t treader;
	int rc;
	void *res;
	
	rc = sem_init(&empty_buffers, 0, 8);               // empty semafor zacina s 8 - cely buffer je k dispozici pro zapis
	if (rc != 0) handle_error_en(rc, "sem_init");
	rc = sem_init(&full_buffers, 0, 0);                // full semafor zacina s 0 - nic nebylo zapsano - nic nelze cist
	if (rc != 0) handle_error_en(rc, "sem_init");

	/* udelej praci */
	rc = pthread_create(&twriter, NULL, &writer, NULL);
	if (rc != 0) handle_error_en(rc, "pthread_create");

	rc = pthread_create(&treader, NULL, &reader, NULL);
	if (rc != 0) handle_error_en(rc, "pthread_create");

	/* posbirej thready */
	rc = pthread_join(twriter, &res);
	if (rc != 0) handle_error_en(rc, "pthread_join");

	rc = pthread_join(treader, &res);
	if (rc != 0) handle_error_en(rc, "pthread_join");

	/* hotovo */
	rc = sem_destroy(&empty_buffers);
	if (rc != 0) handle_error_en(rc, "sem_destroy");
	rc = sem_destroy(&full_buffers);
	if (rc != 0) handle_error_en(rc, "sem_destroy");

	return 0; 
}

void *writer(void *arg) {
	int i;

	for (i = 0; i < 40; i++) {
		sem_wait(&empty_buffers);     // cekej az bude volno v buffer pro zapis
		buffer[i % 8] = 'A' + i;      // zapis do bufferu
		sem_post(&full_buffers);      // rekni reader()u ze je mozno cist
	}
	return NULL;
}
void *reader(void *arg) {
	int i;

	for (i = 0; i < 40; i++) {
		sem_wait(&full_buffers);      // cekej az bude co cist
		printf("%c", buffer[i % 8]);  // zpracuj buffer
		sem_post(&empty_buffers) ;    // uvolni pro dalsi zapis
	}
	printf("\n");
	return NULL;
}


