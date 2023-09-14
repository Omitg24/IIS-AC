#include <stdio.h>

void f(double * pDouble)
{
	*pDouble=4;
}

int main(int argc, char* argv[])
{
	double  d;
	d=3;

	f(&d);
	printf("%f\n",d);
	return 0;
}
