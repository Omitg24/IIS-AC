# Rule to build the main program
bench_fp_mt : bench_fp_mt.o
	gcc bench_fp_mt.o -O3 -o bench_fp_mt -lrt -lm -lpthread

# Sources compilation
bench_fp_mt.o : bench_fp_mt.c
	gcc -c bench_fp_mt.c

# Clean
clean :
	rm -f bench_fp_mt.o
