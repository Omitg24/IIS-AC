#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <pthread.h>

#define MAX_NTASKS_NTHREADS 22 // Maximum number of tasks and threads

//////////////////////////////////////////////////////////////////////////////////
// Start measuring time
// TODO: Write down your DNI without the final letter
//////////////////////////////////////////////////////////////////////////////////
const unsigned int DNI = 32892095; // Example: const unsigned int DNI = 12345678 

const unsigned long NELEMENTS = 55440; // Number of elements to be processed by a task

// Structure with the parameters of each thread
typedef struct
{
	double *data; // Array with data
	unsigned int minIndex; // Minimum array index to process
	unsigned int maxIndex; // Maximum array index to process
} threadArgs_t;

// Data to be proceeeed by the tasks. One pointer per task
double *data[MAX_NTASKS_NTHREADS] ;

// Thread function arguments
threadArgs_t threadArgs[MAX_NTASKS_NTHREADS]; 

int task(unsigned int taskIndex, unsigned int nTaskThreads, pthread_t threadIDs[]);

double mcos(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += cos(val);
	return a;
}

double msin(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += sin(val);
	return a;
}

double mcosh(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += cosh(val);
	return a;
}

double msinh(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += sinh(val);
	return a;
}

double mexp(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += exp(val);
	return a;
}

double mlog(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += log(val);
	return a;
}

double msqrt(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += sqrt(val);
	return a;
}

double mfabs(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += fabs(val);
	return a;
}

double mfloor(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += floor(val);
	return a;
}

double mceil(double val)
{
	double a = 0.0;
	for (int i = 0; i < 50; i++)
		a += ceil(val);
	return a;
}

// Functions to run on each element
const unsigned int NFUNCTIONS = 10;
double (*funcArray[10])(double) = {mcos, msin, mcosh, msinh, mexp, mlog, msqrt, mfabs, mfloor, mceil}; 
unsigned long NTIMES[10] = {40, 20, 10, 9, 6, 5, 4, 3, 2, 1};

int main(int argc, char* argv[])
{
	double elapsed;
	struct timespec start, end;
	
	// Get program arguments
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s ntasks nthreads\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	unsigned int nTasks = atoi(argv[1]);
	unsigned int nThreads = atoi(argv[2]);
	if ((nTasks <= 0) || (nTasks > MAX_NTASKS_NTHREADS))
	{
		fprintf(stderr, "ERROR: task count should be between [1, %d]\n", MAX_NTASKS_NTHREADS);
		exit(EXIT_FAILURE);
	}
	if ((nThreads <= 0) || (nThreads > MAX_NTASKS_NTHREADS))
	{
		fprintf(stderr, "ERROR: thread count should be between [1, %d]\n", MAX_NTASKS_NTHREADS);
		exit(EXIT_FAILURE);
	}
	if (nTasks > 1 && nThreads != nTasks)
	{
		fprintf(stderr, "ERROR: thread count should be equal to task count for task count > 1\n");
		exit(EXIT_FAILURE);		
	}
		
	if (nTasks == 1 && nThreads == 1)		
		printf("Running 1 monolitic task...\n");
	else if (nTasks == 1 && nThreads > 1)
		printf("Running 1 muktithreaded task...\n");
	else
		printf("Running %d monolitic tasks, each on a different thread...\n", nTasks);

	unsigned int nTaskThreads = nThreads / nTasks; // Number of threads for each task
	pthread_t threadIDs[nThreads]; // Thread IDs

	//////////////////////////////////////////////////////////////////////////////////
	// Start measuring time
	// TODO: Write here the appropiate instructions to start time measurement
	//////////////////////////////////////////////////////////////////////////////////
	clock_gettime(CLOCK_REALTIME, &start);

	// Start all the tasks
	for (unsigned int taskIndex = 0; taskIndex < nTasks; taskIndex++)
	{
		// Each task run nTaskThreads threads and saves their IDs into threads array
		if (task(taskIndex, nTaskThreads, threadIDs) < 0)
		{
			fprintf(stderr, "Error running the task %d", taskIndex);
			exit(EXIT_FAILURE);
		}
	}
	
	// Wait for the threads of all the tasks to finish
	for (unsigned int threadIndex = 0; threadIndex < nThreads; threadIndex++)
		pthread_join(threadIDs[threadIndex], NULL);

	// Free memmory
	for (unsigned taskIndex = 0; taskIndex < nTasks; taskIndex++)
		if (data[taskIndex] != NULL)
			free(data[taskIndex]);

	//////////////////////////////////////////////////////////////////////////////////
	// Finish measuring time
	// TODO: Write here the appropiate instructions to finish time measurement
	//////////////////////////////////////////////////////////////////////////////////
	clock_gettime(CLOCK_REALTIME, &end);
	
	printf("Execution finished\n");

	//////////////////////////////////////////////////////////////////////////////////
	// Show the elapsed time
	// TODO: Write here the appropiate instructions to calculate the elapsed time
	//////////////////////////////////////////////////////////////////////////////////
	elapsed = (end.tv_sec - start.tv_sec);
    elapsed += (end.tv_nsec - start.tv_nsec) / 1e+9;
	printf("Elapsed time    : %f s.\n", elapsed);
	
	return 0;
}

// Return a random number in the interval [min, max]
double get_random(unsigned int min, unsigned int max)
{
	return min + (max - min) * ((double)rand()/(double)RAND_MAX);
}

// Function called by every thread
void *thread_job(void *args)
{
	threadArgs_t *threadArgs = (threadArgs_t *)args;
	double *dta = threadArgs->data;
	unsigned int minIndex = threadArgs->minIndex;
	unsigned int maxIndex = threadArgs->maxIndex;
	unsigned int nTimesIndex = (DNI+2) % 10;
	
	for (unsigned int funcIndex = 0; funcIndex < NFUNCTIONS; funcIndex++)
	{
		for (unsigned int i = 0; i < NTIMES[nTimesIndex]; i++)
			for (unsigned int elementIndex = minIndex; elementIndex < maxIndex; elementIndex++)
			{
				funcArray[funcIndex](dta[elementIndex]);
			}
		nTimesIndex++;
		if (nTimesIndex == NFUNCTIONS)
			nTimesIndex = 0;
	}	
	
	return NULL;
}

// Run task of index taskIndex using nTaskThreads threads. Thread IDs are saved in threadIDs
int task(unsigned int taskIndex, unsigned int nTaskThreads, pthread_t threadIDs[])
{
	static unsigned int seed = 0; // Random seed

	// Get memory for the array of random numbers
	data[taskIndex] = (double*)malloc(NELEMENTS * sizeof(double));
	if (data[taskIndex] == NULL)
	{
		printf("ERROR in task %d: Cannot allocate memory\n", taskIndex);
		return -1;
	}

	srand(seed++); // Random seed changes with every task
	
	// Fill the array with random elements
	for (unsigned int i = 0; i < NELEMENTS; i++)
	{
		// Pseudo-random numbers in the interval [1.0, 5.0]
		data[taskIndex][i] = get_random(1, 5);
	}
	
	// Start task threads
	unsigned int nThreadPoints = NELEMENTS / nTaskThreads;
	for (unsigned int threadIndex = 0; threadIndex < nTaskThreads; threadIndex++)
	{
		threadArgs[threadIndex].data = data[taskIndex];
		threadArgs[threadIndex].minIndex = threadIndex * nThreadPoints;
		threadArgs[threadIndex].maxIndex = threadArgs[threadIndex].minIndex + nThreadPoints - 1;
		pthread_t firstThreadId = taskIndex * nTaskThreads; // ID for the first task thread 
		if (pthread_create(&(threadIDs[firstThreadId + threadIndex]), NULL, thread_job, 
		                   &(threadArgs[threadIndex])))
		{
			fprintf(stderr, "ERROR in pthread_create()");
			exit(EXIT_FAILURE);
		}

		printf("Running thread %d of task %d; minIndex = %d, maxIndex = %d\n", 
				threadIndex, taskIndex, threadArgs[threadIndex].minIndex, threadArgs[threadIndex].maxIndex);

	}
	return 0;
}

