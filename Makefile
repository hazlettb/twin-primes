#  
#  Barbara Hazlett
#  hazlettb@onid.oregonstate.edu
#  CS311-400
#  homework #6
#

CC=gcc -lm -pthread -lrt
DEBUG=-g
CFLAGS=$(DEBUG) -Wall 
PROGS=primePThread primeMProc

all: $(PROGS)

primePThread: primePThread.o primePThread.h
	$(CC) $(CFLAGS) -o primePThread primePThread.o

primePThread.o: primePThread.c
	$(CC) $(CFLAGS) -c primePThread.c

primeMProc: primeMProc.o primeMProc.h
	$(CC) $(CFLAGS) -o primeMProc primeMProc.o

primeMProc.o: primeMProc.c
	$(CC) $(CFLAGS) -c primeMProc.c
	
test:
	primeTest.bash

clean:
	rm -f $(PROGS) *.o *~

