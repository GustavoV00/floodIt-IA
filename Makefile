CC=gcc
CFLAGS=-Wall
# DEPS = hellomake.h

# %.o: %.c $(DEPS)

all: floodit

run1:
	./floodit < knapsack.in

run2:
	./knapsack-parallel < knapsack.in

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) 

serial: floodit.o 
	$(CC) -o floodit knapsack-serial.o $(CFLAGS)


clean:
	rm *.o
	rm floodit
	rm knapsack-parallel
