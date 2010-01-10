all: rng aufgabe8_1c aufgabe8_1e

rng:
	$(CC) -g3 -Wall -c rng.c

aufgabe8_1c:
	$(CC) -g3 -Wall -lm -o aufgabe8_1c_binary aufgabe8_1c.c rng.o

aufgabe8_1e:
	$(CC) -g3 -Wall -lm -o aufgabe8_1e_binary aufgabe8_1e.c rng.o

clean:
	rm *_binary *.o
