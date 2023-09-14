#include <stdio.h>

#include "3-4print-pte.h"

int global = 0x12345678;

int main(void)
{
  int local = 0xABCDEF01;

  print_virtual_physical_pte(&global, "Global variable\n"
                                       "------------------\n");
  print_virtual_physical_pte(&local, "Local variable\n"
                                      "-----------------\n");
  print_virtual_physical_pte(print_virtual_physical_pte, "Function\n"
                                                           "----------\n");

  printf("\n---- Press [ENTER] to continue");
  getchar();

  return 0;
}
