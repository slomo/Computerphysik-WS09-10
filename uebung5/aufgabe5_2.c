#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265
#define A -4*Pi 
#define B 4*Pi
#define N 4

double f(double x) {
    return sin(x/2)+sin(x)*sin(x);
}

void distribute_linear(double *x, int n)
{
    int i;
    for(i=0;i<=n;++i){
        x[i]=A+i*((B-A)/n);
    }
}

double dft(double *h,n,m) {
    double result;
    int i;
    for(i=0;i<N;i++) {
        result+=h[i]*exp((2*Pi*i*
    }
}

int main(int argc, char* argv[])
{
    double probes[100],a[4][4],x[4]={-2,-1,1,2},result;
    int i,j=0;
    FILE *fallout;

    fallout = fopen("aufgabe5_1.out","w");

    distribute_linear(probes,100);

    a[0][0]=f(x[0]);
    a[0][1]=2;
    a[0][2]=3;
    a[0][3]=4;
    a[1][0]=f(x[1]);
    a[1][1]=6;
    a[1][2]=7;
    a[1][3]=8;
    a[2][0]=f(x[2]);
    a[2][1]=10;
    a[2][2]=11;
    a[2][3]=12;

    for(i=0;i<100;i++) {
        if ((probes[i] == -1) || (probes[i] == 1)) {
            j++;
            printf("%d\n",j);
        }
        result=a[j][0]+a[j][1]*(probes[i]-x[j])+a[j][2]*pow((probes[i]-x[j]),2)+a[j][3]*pow((probes[i]-x[j]),3);
        fprintf(fallout,"%f %f\n",probes[i],result);
    }

    fclose(fallout);

return EXIT_SUCCESS;
}
