CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJS = main.o maxHeap.o
TESTOBJS = test.o unitTest.o
EXE = run
TEST = test

all: $(EXE) $(TEST)

$(EXE):$(OBJS)
	$(CC) $(CFLAGS) -o run $(OBJS)
$(TEST): $(OBJS) $(TESTOBJS)
	$(CC) $(CFLAGS) maxHeap.o $(TESTOBJS) -o $(TEST)


main.o:main.c
	$(CC) $(CFLAGS) -c main.c
maxHeap.o:maxHeap.c maxHeap.h
	$(CC) $(CFLAGS) -c maxHeap.c


test.o: test.c
	$(CC) $(CFLAGS) -c test.c
unitTest.o: unitTest.c unitTest.h
	$(CC) $(CFLAGS) -c unitTest.c

clean: 
	rm $(OBJS) $(TESTOBJS) $(EXE) $(TEST)
