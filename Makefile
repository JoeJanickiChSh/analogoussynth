CC = gcc
LINKFLAGS = -lSDL2
INCFLAGS = -Iinclude
EXECUTABLE = Analogous
SRC = src/*.c

all:
	$(CC) $(SRC) $(INCFLAGS) $(LINKFLAGS) -o $(EXECUTABLE)

run:
	make
	./$(EXECUTABLE)
