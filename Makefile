CC=gcc

main: minimax.o obstruction.o main.c
	$(CXX) minimax.o obstruction.o main.c -o main

minimax.o: minimax.c obstruction.o
	$(CXX) -c minimax.c

obstruction.o: obstruction.c
	$(CXX) -c obstruction.c

clean:
	rm *.o
	rm main

run:
	./main
