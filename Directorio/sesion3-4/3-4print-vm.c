#include <stdio.h>

#include "3-4print-pte.h"

int main(void)
{
	int local = 0xABCDEF01;

	print_virtual_physical_pte(&local, "Local variable\n-----------------");

	printf("\n---- Press [ENTER] to continue");
	getchar();

	return 0;
}
