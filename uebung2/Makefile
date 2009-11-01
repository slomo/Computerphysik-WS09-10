all: aufgabe2_2 aufgabe2_4 aufgabe2_6 aufgabe2_4_with_gmp

aufgabe2_2:
	$(CC) -Wall -lm -o aufgabe2_2 aufgabe2_2.c

aufgabe2_4:
	$(CC) -Wall -lm -o aufgabe2_4 aufgabe2_4.c

aufgabe2_6:
	$(CC) -Wall -o aufgabe2_6 aufgabe2_6.c

aufgabe2_4_with_gmp:
	echo WARNING this Step may fail when GMP libary is not installed
	$(CC) -Wall -lm -lgmp -o aufgabe2_4_gmp -DGMP aufgabe2_4.c

clean:
	rm aufgabe2_2 aufgabe2_4 aufgabe2_6
