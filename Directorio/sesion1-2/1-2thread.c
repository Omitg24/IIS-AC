#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* ThreadProc(void* arg)
{
	const int TIMES = 6;
	int i;

	// Cast
	int n = *((int*)arg);
	for (i = 0; i < TIMES; i++)
	{
		printf("Thread %d, message %d\n", n, i);
		sleep(1);  // Sleep 1 second
	}
	printf("Thread %d finished.\n", n);
	return NULL;
}

int main(int argc, char* argv[])
{
	const int N = 5;
	const int TIMES = 3;
	pthread_t thread[N];
	int i;
	int a[N];

	// Thread creation
	for (i = 0; i < N; i++)
	{
		a[i]=i;
		if (pthread_create(&thread[i], NULL, ThreadProc, &a[i]) != 0)
		{
			fprintf(stderr, "ERROR: Creating thread %d\n", i);
			return EXIT_FAILURE;
		}
	}

	for (i = 0; i < TIMES; i++)
	{
		printf("Main thread, message %d\n", i);
		sleep(1);  // Sleep 1 second
	}

	// Wait till the completion of all threads
	printf("Main thread waiting...\n");
	for (i = 0; i < N; i++)
	{
		pthread_join(thread[i], NULL);
	}
	printf("Main thread finished.\n");
	return EXIT_SUCCESS;
}
