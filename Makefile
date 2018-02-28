CFLAGS=-std=c99 -Wall -O2
LIB=medfilt
COBJS=$(LIB).o

all: test

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

lib$(LIB).a: $(COBJS)
	$(AR) rc $@ $^

test: test_$(LIB).o | lib$(LIB).a
	$(CC) $^ -o $@ -l$(LIB) -L.

run: test
	./test

clean:
	$(RM) *.o *.a *.exe
