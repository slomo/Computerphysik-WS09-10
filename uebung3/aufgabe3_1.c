#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define A -1.0
#define B 1.0
#define PI 3.14159265
#define X (PI/4)

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

void distribute_tschebyscheff(double *x, int n){ 
    int i;
    for(i=0;i<=n;++i){
        x[i]=cos(((i+0.5)/(n+1))*PI);
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
    int n;
    double *t,*a,*x,result;

    if(argc==3) {
        
        n = atoi(argv[2]);
        
        t = malloc((sizeof(double)*(n+1)));
        a = malloc((sizeof(double)*(n+1)));
        x = malloc((sizeof(double)*(n+1)));

        if(!strcmp(argv[1],"-l")) {
            distribute_linear(x,n);
        }
        if(!strcmp(argv[1],"-t")) {
            distribute_tschebyscheff(x,n);
        }
        
        compute_polynomial(x,t,n,a);

        result=compute_horner(x,a,n);

        printf("n=%d\nx=%f\np=%f\ndelta=%E\n",n,X,result,fabs(result-f(X)));

        free(t);
        free(a);
        free(x);
    }
    else {
        printf("Usage: %s <-l|-t> <n>\n-l Linear distribution\n-t Tschebyscheff distribution\n",argv[0]);
    }

    return EXIT_SUCCESS;
}
