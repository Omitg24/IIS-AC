/* Disable interrupts for several seconds */

int main() {
  long int i, j; 

  /* Disable interrupts */
  __asm__(
    "cli"
  );
  
  /* Wait for several seconds */
  for (i = 0; i < 5000; i++)
    for (j = 0; j < 1000000; j++);

  /* At the exit of any program status register is restored,
     so interrupts are enabled again */
}
