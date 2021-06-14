CC=gcc

TARGET=main
COMMAND=obstruction.c main.c -o $(TARGET)

all:
	$(CC) $(COMMAND)

clean:
	rm $(TARGET)
