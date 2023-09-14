#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "3-4print-pte.h"

int main(void)
{
  void *p;         /* Pointer to the requested memory area */

  ////////////////////////////////////
  // A 16-KiB memory area is requested
  ////////////////////////////////////

  if ((p = malloc(16*1024)) == NULL)
    {
      fprintf(stderr, "Error in malloc\n");
      return(-1);
    }

  printf("\nProcess Identifier (PID): %d\n", getpid());

  ////////////////////////////////////////////////////////////////
  // What is the physical address associated with the memory area?
  ////////////////////////////////////////////////////////////////
  print_virtual_physical_pte(p, "The requested memory area\n"
                                 "-----------------------------");

  printf("\n---- Press [ENTER] to continue");
  getchar();

  /////////////////////////////////////
  // The 16-KiB memory area is released
  /////////////////////////////////////
  free(p);

  return 0;
}
