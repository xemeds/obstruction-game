# Compiler
CC=gcc

# Target file name
TARGET=obstruction

all:
	$(CC) obstruction.c -o $(TARGET)

clean:
	rm $(TARGET)
