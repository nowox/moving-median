CFLAGS=-std=c99 -Wall -O2
COBJS=moving_median.o

all: test

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

libmedfilt.a: $(COBJS)
	$(AR) rc $@ $^

test: test_moving_median.o
	$(CC) $^ -o $@ -lmedfilt -L.

run: test
	./test
