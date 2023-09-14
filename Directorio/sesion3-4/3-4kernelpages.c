#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atc/linmem.h>

const unsigned int PAGE_SIZE    = 4096;
const unsigned int OS_BASE_ADDR = 0xC0000000;
const char KERNEL_CODE_STR[]    = "Kernel code";
const char KERNEL_DATA_STR[]    = "Kernel data";
const char KERNEL_BSS_STR[]     = "Kernel bss";
const unsigned int MAX_LINE_SIZE = 256;

/* Kernel physical addresses */ 
typedef struct
{
	unsigned int minKernelCode;
	unsigned int maxKernelCode;
	unsigned int minKernelData;
	unsigned int maxKernelData;	
	unsigned int minKernelBss;
	unsigned int maxKernelBss;	
} kernel_addr_t;

/* Get kernel physical addresses from system file /proc/iomem */
int get_kernel_phy_addr(kernel_addr_t *kernelAddr)
{
	FILE *file;
	unsigned int minKernelCode = 0, maxKernelCode = 0;
	unsigned int minKernelData = 0, maxKernelData = 0;
	unsigned int minKernelBss  = 0, maxKernelBss  = 0;
	char line[MAX_LINE_SIZE];

	if ((file = fopen("/proc/iomem", "r")) == NULL)
		return -1;
	while (minKernelCode == maxKernelCode || minKernelData == maxKernelData ||
		minKernelBss == maxKernelBss)
	{
		if (fgets(line, MAX_LINE_SIZE, file) == NULL)
			return -1;
		if (strstr(line, KERNEL_CODE_STR) != NULL)
			sscanf(line, "%x-%x", &minKernelCode, &maxKernelCode);
		if (strstr(line, KERNEL_DATA_STR) != NULL)
			sscanf(line, "%x-%x", &minKernelData, &maxKernelData);
		if (strstr(line, KERNEL_BSS_STR)  != NULL)
			sscanf(line, "%x-%x", &minKernelBss, &maxKernelBss);
	}
	kernelAddr->minKernelCode  = minKernelCode;
	kernelAddr->maxKernelCode  = maxKernelCode;
	kernelAddr->minKernelData  = minKernelData;
	kernelAddr->maxKernelData  = maxKernelData;
	kernelAddr->minKernelBss   = minKernelBss;
	kernelAddr->maxKernelBss   = maxKernelBss;
	return 0;
}

/* Get first kernel code, first kernel data and first kernel bss pages in memory */
int get_kernel_pages_memory(unsigned int *codePage, unsigned int *dataPage, 
	unsigned int *bssPage, kernel_addr_t *kernelAddr)
{
	unsigned int addr;
	unsigned int pte;
	unsigned minAddr, maxAddr;

	*codePage = *dataPage = *bssPage = 0;

	/* Test if linmem module is running */
	if (get_pte((void *)0, NULL) < 0)
		return -1;
	
	/* Look for the first kernel code page present in physical memory */
	minAddr = kernelAddr->minKernelCode + OS_BASE_ADDR;
	maxAddr = kernelAddr->maxKernelCode + OS_BASE_ADDR;
	for (addr = minAddr; addr <= maxAddr; addr += PAGE_SIZE) 
	{
		if (get_pte((void *)addr, &pte) == 0)
			if (pte & 1) /* If the page is in memory */
			{
				*codePage = (addr & 0xFFFFF000) >> 12;
				break;
			}
	}
	if (addr > kernelAddr->maxKernelCode + OS_BASE_ADDR) /* Failed to find the code page*/
		return -2;
	
	/* Look for the first kernel data page present in physical memory */
	minAddr = kernelAddr->minKernelData + OS_BASE_ADDR;
	maxAddr = kernelAddr->maxKernelData + OS_BASE_ADDR;
	for (addr = minAddr; addr <= maxAddr; addr += PAGE_SIZE) 
	{
		if (get_pte((void *)addr, &pte) == 0)
			if (pte & 1) /* If the page is in memory */
			{
				*dataPage = (addr & 0xFFFFF000) >> 12;
				break;
			}
	}
	if (addr > kernelAddr->maxKernelData + OS_BASE_ADDR) /* Failed to find the data page*/
		return -2;
		
	/* Look for the first kernel bss page present in physical memory */
	minAddr = kernelAddr->minKernelBss + OS_BASE_ADDR;
	maxAddr = kernelAddr->maxKernelBss + OS_BASE_ADDR;
	for (addr = minAddr; addr <= maxAddr; addr += PAGE_SIZE) 
	{
		if (get_pte((void *)addr, &pte) == 0)
			if (pte & 1) /* If the page is in memory */
			{
				*bssPage = (addr & 0xFFFFF000) >> 12;
				break;
			}
	}
	if (addr > kernelAddr->maxKernelBss + OS_BASE_ADDR) /* Failed to find the data page*/
		return -2;

	return 0;
}

int main()
{
	kernel_addr_t kernelAddr;
	unsigned int codePage, dataPage, bssPage;
	unsigned int codeFrame, dataFrame, bssFrame;
	unsigned int codeFlags, dataFlags, bssFlags;
	unsigned int pte;
	
	/* Get kernel code and data physical addresses */
	if (get_kernel_phy_addr(&kernelAddr) < 0)
	{
		fprintf(stderr, "\nError. Try running with sudo\n\n");
		return EXIT_FAILURE;
	}
	printf("\nKernel code addresses: %08Xh-%08Xh\n", 
		kernelAddr.minKernelCode, kernelAddr.maxKernelCode);
	printf("Kernel data addresses: %08Xh-%08Xh\n", 
		kernelAddr.minKernelData, kernelAddr.maxKernelData);
	printf("Kernel bss  addresses: %08Xh-%08Xh\n", 
		kernelAddr.minKernelBss, kernelAddr.maxKernelBss);
	
	/* Get first kernel code, data and bss pages in memory */
	if (get_kernel_pages_memory(&codePage, &dataPage, &bssPage, &kernelAddr) < 0)
	{
		fprintf(stderr, "\nPages in memory not found. Test if linmem is running\n\n");
		return(EXIT_FAILURE);
	}
	printf("\nFirst kernel code page in memory: %05Xh\n", codePage);
	printf("First kernel data page in memory: %05Xh\n", dataPage);
	printf("First kernel bss  page in memory: %05Xh\n", bssPage);
	
	/* Calculate the frame and flags for the kernel code, data and bss pages:
		codeFrame, codeFlags,
		dataFrame, dataFlags
		bssFrame,  bssFlags */
	<<Complete>>
	
	printf("\nKernel code page %05Xh ---> Frame: %05Xh; Flags: %03Xh\n", codePage, codeFrame, codeFlags);
	printf("Kernel data page %05Xh ---> Frame: %05Xh; Flags: %03Xh\n", dataPage, dataFrame, dataFlags);	
	printf("Kernel bss  page %05Xh ---> Frame: %05Xh; Flags: %03Xh\n\n", bssPage, bssFrame, bssFlags);	
}
