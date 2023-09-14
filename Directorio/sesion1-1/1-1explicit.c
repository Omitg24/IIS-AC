#include <stdio.h>

int main() {
<<<<<<< HEAD
	int x=1;

	const char *p= (const char*)&x;

	if (*p) {
		printf("Little-endian\n"); 
=======
	int x = 1;

	const char *p =(const char*)&x;

	if (*p) {
		printf("Little-endian\n");
>>>>>>> 9788fea50d6dc919180e25faf591c43ef06d545d
	}
	else {
		printf("Big-endian\n");
	}

	return 0;
<<<<<<< HEAD
=======

>>>>>>> 9788fea50d6dc919180e25faf591c43ef06d545d
}
