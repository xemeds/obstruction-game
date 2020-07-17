CC=gcc  #compiler
TARGET=obstruction #target file name
 
all:
	$(CC) obstruction.c -o $(TARGET)
 
clean:
	rm $(TARGET)
