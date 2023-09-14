# Rule to build the main program
bench_fp : bench_fp.o
	gcc bench_fp.o -O3 -o bench_fp -lrt -lm

# Sources compilation
bench_fp.o : bench_fp.c
	gcc -c bench_fp.c

# Clean
clean :
	rm -f bench_fp.o
