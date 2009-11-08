all: aufgabe3_1 aufgabe3_2 plot

aufgabe3_1:
	$(CC) -Wall -lm -o aufgabe3_1 aufgabe3_1.c

plot:
	gnuplot aufgabe3_2.dem

aufgabe3_2:
	$(CC) -Wall -lm -o aufgabe3_2 aufgabe3_2.c

clean:
	rm aufgabe3_1 aufgabe3_2
