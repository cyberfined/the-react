CC=gcc
SRC=$(wildcard *.c)
CFLAGS=-c -Wall
OBJ=$(SRC:.c=.o)
LDFLAGS=-lSDL2 -lGL -lGLU -lm
BINDIR=bin
TARGET=react
.PHONY: all clean
all: $(TARGET)
$(TARGET): compile
	rm -rf $(BINDIR)
	@mkdir $(BINDIR)
	$(CC) $(OBJ) -o $(BINDIR)/$(TARGET) $(LDFLAGS)
compile:
	$(CC) $(SRC) $(CFLAGS)
clean:
	rm -rf *.o $(BINDIR)
