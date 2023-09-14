#include <stdio.h>

#define NUM_ELEMENTS 7

int add(int vector[], int num)
{
        int suma=0;
        for (int i=0; i<num; i++){
                suma=suma+vector[i];
        }
        return suma;
}
int main()
{
	int vector[NUM_ELEMENTS] = {2, 5, -2, 9, 12, -4, 3};
	int result;

	result = add(vector, NUM_ELEMENTS);
	printf("The addition is: %d\n", result);
	return 0;
}
