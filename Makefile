CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g -Ofast -m64
OBJS=gettime.o utils.o

%_debug.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $< -DDEBUG
%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

all: primes sde_segmented sde_segmented_debug

utils.o: utils.c utils.h
gettime.o: gettime.c gettime.h
primes.o: primes.c gettime.h utils.h
sde_segmented.o: sde_segmented.c gettime.h utils.h
sde_segmented_debug.o: sde_segmented.c gettime.h utils.h

primes: $(OBJS) primes.o
	$(CC) $(CFLAGS) -o $@ $^

sde_segmented: sde_segmented.o $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

sde_segmented_debug: sde_segmented_debug.o $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

p10000: p10000.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o primes
