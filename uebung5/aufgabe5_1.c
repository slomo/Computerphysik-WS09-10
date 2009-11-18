#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define A -5.0
#define B 5.0
#define PI 3.14159265
#define X (PI/4)
#define N 4

/*
 * The value PI/4 is close to the borders of the interval, so the 
 * oscillation can become a disturbing factor, especally with 
 * linear distribution.
 * The rounded value of f(PI/4) is 0.30448
 * Here now the results for our interpolation
 *
 * #IValues p(X)lin delta   p(X)tsh delta
 * 5       -0.21491 0.51839 0.19445 0.11003
 * 12       2.69779 2.39331 0.17126 0.13322
 * 22       5.13411 4.82963 0.32770 0.02186
 *
 * It cann be seen that the best approch to the actual value comes
 * with tschebyscheff distribution and 22 interpolation vaules, wich
 * goes along with the results from task 2.
 */


double f(double x)
{
    return 5/(1+25*x*x);
}

void distribute_linear(double *x, int n)
{
    int i;
    for(i=0;i<=n;++i){
        x[i]=A+i*((B-A)/n);
    }
}

void compute_polynomial(double *x,double *t,int n,double *a){
    int i,j;

    for(i=0;i<=n;++i) {
        t[i]=f(x[i]);
        if(i>=1) {
            for(j=i-1;j>=0;--j) {
                t[j]=(t[j+1]-t[j])/(x[i]-x[j]);
            }
        }
            a[i]=t[0];
    }
}

double compute_horner(double *x,double *a,int n){
    double p=a[n];
    int i;

    for(i=n-1;i>=0;--i) {
        p=p*(X-x[i])+a[i];
    }
    return p;
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
