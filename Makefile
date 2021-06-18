CC=gcc

main: minimax.o obstruction.o main.c
	$(CC) minimax.o obstruction.o main.c -o main

minimax.o: minimax.c obstruction.o
	$(CC) -c minimax.c

obstruction.o: obstruction.c
	$(CC) -c obstruction.c

clean:
	rm *.o
	rm main

run:
	./main
