#include <stdio.h>
#include <stdlib.h>

#define N 4

double f(double x)
{
    return 5/(1+25*x*x);
}

int main(int argc, char** argv)
{
	double x[N] = {-2,-1,1,2};
    double d[N], lambda[N], mu[N], h[N], y[N];
    double matrix[N][N];
    
    int j,i;
    
    
    //Initialisierung
    lambda[0]=0;
    d[0]=0;
    mu[N-1]=0;
    d[N-1]=0;
        
    //Berechung
    for(j=0;j<N;j++) {
        y[j]=f(x[j]);
        h[j]=x[j]-x[j-1];
    }
    for(j=1;j<N-1;j++) {
        d[j]=(6/(h[j]+h[j+1]))*(((y[j+1]-y[j])/h[j+1])-((y[j]-y[j-1])/h[j]));
        lambda[j]=h[j+1]/(h[j]+h[j+1]);
        mu[j]=h[j]/(h[j]+h[j+1]);
    }
    
    //Eintragen ins array
    for(j=0;j<N;j++) {
        for(i=0;i<N;i++) {
            if(i==(j+1)) {
                matrix[j][i]=lambda[j];
            }
            else if(i==(j-1)) {
                matrix[j][i]=mu[j];
            }
            else if (i==j) {
                matrix[j][i]=2;
            }
            else {
                matrix[j][i]=0;
            }
        }
    }
    
    //Ausgabe
    for(j=0;j<N;j++) {
        printf("| ");
        for(i=0;i<N;i++) {
            printf("%.2f ",matrix[j][i]);
        }
        printf("|  |M%d|  |%f|\n",j,d[j]);
    }
    
	return EXIT_SUCCESS;
}
