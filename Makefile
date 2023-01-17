CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g -Ofast -m64
DEP=gettime.h
OBJS=primes.o gettime.o

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

all: primes

primes: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o primes
