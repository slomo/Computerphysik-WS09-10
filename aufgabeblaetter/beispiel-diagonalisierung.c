/**

Dieses Programm ist ein Beispiel zur Diagonalisierung einer 3x3 Matrix mit Hilfe der 
Routinen in diagonalisierung.c. Fuer die Uebungsaufgabe soll natuerlich die Matrixdarstellung
des Hamiltonians im Ortsraum verwendet werden. Die Eigen-"Vektoren", die von der Routine jacobi()
zurueckgeliefert werden, sind dementsprechend die Ortsdarstellungen der Eigenzustaende (der
Wellenfunktionen!) des Problems, jeweils zu den entsprechenden Eigenwerten (Energie-Eigenwert!)

Kompilierung mit

gcc beispiel-diagonalisierung.c diagonalisierung.c -lm

*/

#include <stdio.h>
#include "diagonalisierung.h"


int main() {
        float **a = matrix(1, 3, 1, 3); // input matrix
        float **v = matrix(1, 3, 1, 3); // output matrix with eigenvectors
        float *d = vector(1, 3);        // output vector of eigenvalues
        int rot = 0;

        // test matrix
        a[1][1] = 0;
        a[1][2] = 1.;
        a[1][3] = -1.;
        a[2][1] = 1.0;
        a[2][2] = 1.0;
        a[2][3] = 0;
        a[3][1] = -1.0;
        a[3][2] = 0;
        a[3][3] = 1.0;

        jacobi(a, 3, d, v, &rot); // caluclate eigenvalues and eigenvectors
        eigsrt(d, v, 3);          // sort eigenvalues and vectors

        // output
	int i, j;
        printf("Eigenwerte: \n");
        for(i = 1; i <= 3; i++) {
          printf(" %5.3f", d[i]);
        }
        printf("\n\nEigenvektoren (bzw Eigenfunktion): \n");
        for(i = 1; i <= 3; i++) {
        	for(j = 1; j <= 3; j++) {
                	printf(" %5.3f", v[i][j]);
        	}
		printf("\n");
        }
	return 0;
}
