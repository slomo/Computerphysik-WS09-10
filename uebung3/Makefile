all: aufgabe3_1 plot

aufgabe3_1:
	$(CC) -Wall -lm -o aufgabe3_1 aufgabe3_1.c

plot:
	gnuplot aufgabe3_2.dem
	ps2pdf aufgabe3_2.ps

clean:
	rm aufgabe3_1
