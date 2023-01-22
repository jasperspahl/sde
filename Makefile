CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g -Ofast -m64
DEP=gettime.h utils.h Makefile
OBJS=gettime.o utils.o

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

all: primes sde_segmented

primes: $(OBJS) primes.o
	$(CC) $(CFLAGS) -o $@ $^

sde_segmented: sde_segmented.o $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

p10000: p10000.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o primes
