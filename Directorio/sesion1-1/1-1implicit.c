#include <stdio.h>

int main(){
	double div = 3.75;
	int num = 6;
	int result = num/(int)div;
	printf("Variable result is %d, but the division was %f\n", result, num /div);
	return 0;
}
