CFLAGS=-std=c99 -Wall -O2
LIB=medfilt
COBJS=$(LIB).o

cstat-db=cstat.db

all: test

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
	#icstat.exe --db $(cstat-db) --checks cstat-checks.txt analyze -- iccarm $<
	#ireport.exe --db $(cstat-db) --output report.html --project qsort --full

lib$(LIB).a: $(COBJS)
	$(AR) rc $@ $^

test: test_$(LIB).o | lib$(LIB).a
	$(CC) $^ -o $@ -l$(LIB) -L.

run: test
	./test

clean:
	$(RM) *.o *.a *.exe
