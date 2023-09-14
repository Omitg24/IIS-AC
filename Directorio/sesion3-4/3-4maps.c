#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {

  printf("\nProcess Identifier (PID): %d\n", getpid());

  printf("\nPress [ENTER] to continue\n");
  getchar(); /* Wait for ENTER */

  return 0;
}
