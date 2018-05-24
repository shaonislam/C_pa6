CC = gcc
CFLAGS = -Wall -ansi
TARGET = runsim
OBJ = runsim.o
TARGET1 = testsim
OBJ1 = testsim.o
all: $(TARGET) $(TARGET1)

runsim: $(OBJ)
	$(CC) $(CFLAGS) -o runsim $(OBJ)

testsim: $(OBJ1)
	$(CC) $(CFLAGS) -o testsim $(OBJ1)

runsim.o: runsim.c
	$(CC) $(CFLAGS) -c runsim.c

testsim.o: testsim.c
	$(CC) $(CFLAGS) -c testsim.c

clean:
	/bin/rm -f *.o (OBJ) $(TARGET) $(OBJ1) $(TARGET1)


