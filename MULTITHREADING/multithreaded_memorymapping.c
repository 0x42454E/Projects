/********************************************************************
 * Multithreading Example with pthreads
 * ---------------------------------------------------------------
 * Demonstrates creation and termination of three threads (A, B, C)
 * from the main thread using the pthreads library.
 *
 * Each thread prints its identity and exits with a status value.
 * The main thread creates all three and then exits itself.
 *
 * Notes:
 * - Each thread performs a dummy loop influenced by its thread ID
 * - Incorrect casts: pthread_t should not be directly cast to int
 * - Thread attributes passed incorrectly in `pthread_create`
 *   (e.g., `(void *)thr_b` instead of `NULL`)
 * - Return values from threads are not joined or inspected
 *
 * Purpose: Practice pthread creation, identity printing, and exits
 ********************************************************************/


#include <stdio.h>
#include <pthread.h>

void *sub_a(void *);
void *sub_b(void *);
void *sub_c(void *);

pthread_t thr_a, thr_b, thr_c;

int main()
{

	pthread_t main_thr = pthread_self();

	printf("Main thread = %ld\n", main_thr); 

	if (pthread_create(&thr_a, NULL, sub_a, &main_thr))
	{
		fprintf(stderr,"Can't create thr_a\n");
		return 0;
	}

	if (pthread_create(&thr_b, (void *)thr_b, sub_b, &thr_a))
	{
		fprintf(stderr,"Can't create thr_b\n");
		return 0;
	}

	if (pthread_create(&thr_c, (void *)thr_c, sub_c, &thr_b))
	{
		fprintf(stderr,"Can't create thr_c\n");
		return 0;
	}

	printf("Main Created threads A:%ld B:%ld C:%ld\n", thr_a, thr_b, thr_c); 
	printf("Main Thread exiting...\n"); 
	pthread_exit((void *)main_thr);
	
	return 0;
}

void *sub_a(void *arg)
{
	int i = 0;
	printf("A: In thread A...\n"); 

	for (i = 0; i < 1000000 * (int)pthread_self(); ++i)
	{
		printf("A: Thread exiting...\n"); 
		pthread_exit((void *)77);
	}
	
	return NULL;
}

void * sub_b(void *arg)
{
	int i = 0;

	printf("B: In thread B...\n"); 

	for (i = 0; i < 1000000 * (int)pthread_self(); ++i)
	{
		printf("B: Thread exiting...\n"); 
		pthread_exit((void *)66);
	}
	
	return NULL;
}

void * sub_c(void *arg)
{
	int i = 0;

	printf("c: In thread c...\n"); 

	for (i = 0; i < 1000000 * (int)pthread_self(); ++i)
	{
		printf("c: Thread exiting...\n"); 
		pthread_exit((void *)66);
	}
	
	return NULL;
}

