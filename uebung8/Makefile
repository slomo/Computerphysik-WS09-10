all: rng aufgabe8_1c

rng:
	$(CC) -Wall -c rng.c

aufgabe8_1c:
	$(CC) -Wall -lm -o aufgabe8_1c_binary aufgabe8_1c.c rng.o

clean:
	rm *_binary *.o
