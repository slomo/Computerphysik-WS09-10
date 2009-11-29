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
    double probes[100],a[4][4],x[4]={-2,-1,1,2},result,y[4],h[4];
    int i,j=0;
    FILE *fallout;

    fallout = fopen("aufgabe5_1.out","w");

    distribute_linear(probes,100);

    /* | 2.00 0.00 0.00 0.00 |  |M0|  |0.000000|
     * | 0.33 2.00 0.67 0.00 |  |M1|  |-0.285605|
     * | 0.00 0.67 2.00 0.33 |  |M2|  |-0.285605|
     * | 0.00 0.00 0.00 2.00 |  |M3|  |0.000000|
     * 
     * Solution M0 = 0, M1 = -0.107101875, M2 = -0.107101875, M3 = 0
     */ 
    double M[4]={0,-0.107101875,-0.107101875,0};
    
    for(i=0;i<N;i++) {
        y[i]=f(x[i]);
        h[i]=x[i]-x[i-1];
    }

    for(i=0;i<=2;i++) {
        a[j][0]=f(x[j]);
        a[0][1]=(y[j+1]-y[j])/h[j+1] - (2*M[j]+M[j+1])/6 * h[j+1];
        a[0][2]=M[j]/2;
        a[0][3]=(M[j+1]-M[j])/(6*h[j+1]);
    }

    for(i=0;i<100;i++) {
        if ((probes[i] == -1) || (probes[i] == 1)) {
            j++;
        }
        result=a[j][0]+a[j][1]*(probes[i]-x[j])+a[j][2]*pow((probes[i]-x[j]),2)+a[j][3]*pow((probes[i]-x[j]),3);
        fprintf(fallout,"%f %f\n",probes[i],result);
    }

    fclose(fallout);

return EXIT_SUCCESS;
}
