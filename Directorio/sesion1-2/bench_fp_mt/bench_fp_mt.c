#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

void *Task(void *v);
void DoFloatingPoint(unsigned long nElements, unsigned long nTimes);

const unsigned short NUM_THREADS = 10;

int main(int argc, char* argv[])
{
	struct timespec tStart, tEnd;
	double dElapsedTimeS;
	unsigned short i;

	// Start measuring time	
	printf("Running task    : ");
	fflush(stdout);

	// TODO: if (...)
	if(clock_gettime(CLOCK_REALTIME, &tStart)!=0)
	{
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}

	pthread_t Threads[NUM_THREADS];
	for (i = 0; i < NUM_THREADS; i++)
	{
		int pthread_ret = pthread_create(&Threads[i], NULL, Task, NULL);
		if (pthread_ret)
		{
			printf("ERROR: pthread_create error code: %d.\n", pthread_ret);
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(Threads[i], NULL);

	// Finish measuring time
	// TODO: if (...)
	if(clock_gettime(CLOCK_REALTIME, &tEnd)!=0)
	{
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}

	printf("Finished\n");

	// Show the elapsed time
	dElapsedTimeS = (tEnd.tv_sec - tStart.tv_sec);
    dElapsedTimeS += (tEnd.tv_nsec - tStart.tv_nsec) / 1e+9;
	printf("Elapsed time    : %f s.\n", dElapsedTimeS);

	return 0;
}

void *Task(void *v)
{
	DoFloatingPoint(100000, 100);
	DoFloatingPoint(10000, 1000);
	DoFloatingPoint(1000, 10000);
	DoFloatingPoint(100, 100000);
}

void DoFloatingPoint(unsigned long nElements, unsigned long nTimes)
{
	unsigned long i, j;
	static unsigned int seed = 0;

	double *pdSrc1 = (double*)malloc(nElements * sizeof(double));
	double *pdSrc2 = (double*)malloc(nElements * sizeof(double));
	double *pdDest = (double*)malloc(nElements * sizeof(double));
	if ( pdSrc1 == NULL || pdSrc2 == NULL || pdDest == NULL )
	{
		free(pdSrc1);
		free(pdSrc2);
		free(pdDest);
		printf("ERROR in DoFloatingPoint: Cannot allocate memory\n");
		exit(EXIT_FAILURE);
	}

	srand(seed++);
	for (i = 0; i < nElements; i++)
	{
		// Pseudo-random numbers in the interval [1.0-2.0]
		pdSrc1[i] = 1.0 + ((double)rand()/(double)RAND_MAX);
		pdSrc2[i] = 1.0 + ((double)rand()/(double)RAND_MAX);
	}

	for (j = 0; j < nTimes; j++)
	{
		for (i = 0; i < nElements; i++)
		{
			pdDest[i] = pdSrc1[i] / pdSrc2[i];
			pdDest[i] = pdDest[i] * pdSrc1[i];
			pdDest[i] = pdDest[i] + pdSrc1[i];
			pdDest[i] = pdDest[i] - pdSrc2[i];
			pdDest[i] = sqrt(pdDest[i]);
			pdDest[i] = sin(pdDest[i]);
		}
	}

	free(pdSrc1);
	free(pdSrc2);
 	free(pdDest);
}