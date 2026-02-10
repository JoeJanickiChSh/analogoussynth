CC = gcc
LINKFLAGS = -lSDL2
INCFLAGS = -Iinclude
EXECUTABLE = Analogous
DBGFLAGS = -g
SRC = src/*.c

all:
	$(CC) $(DBGFLAGS) $(SRC) $(INCFLAGS) $(LINKFLAGS) -o $(EXECUTABLE)

run:
	make
	./$(EXECUTABLE)
