#include <stdio.h>
#include <atc/linmem.h>

//#include "3-4print-pte.h"

// Given a virtual address, its virtual address is displayed on the screen,
// as well as its associated page table entry (pte), physical address and
// flags of the memory page. On top of this information, the title passed
// as argument is also displayed.
void print_virtual_physical_pte(void *virtual_addr, char *title)
{
	unsigned int physical_addr;
	unsigned int pte;
	unsigned int flags_vp;

	printf("\n%s\n", title); // Print the title

	// Get the page table entry for the virtual address
	if (get_pte(virtual_addr, &pte))
	{
		perror("Linmem module error");
		return;
	}

	// If the page is in memory (i.e, if the present bit is one)
	if ((pte & 0x00000001) == 1)
	{
		// Store the flags associated to the memory page
		flags_vp = <<Complete 1>>

		// Calculate the memory physical address
		physical_addr = <<Complete 2>>
		
		// Print address info
		printf("Virtual address: \t%.8Xh\n"
		       "Page Table Entry:\t%.8Xh\n"
		       "Physical Address:\t%.8Xh\n"
		       "Flags Virtual Page:\t%.3Xh\n",
		       (unsigned int)virtual_addr, pte, physical_addr, flags_vp);
	}
	else
	{
		fprintf(stderr, "Page %.5Xh has no page frame allocated\n",
			(unsigned int)virtual_addr >> 12);
	}
}
