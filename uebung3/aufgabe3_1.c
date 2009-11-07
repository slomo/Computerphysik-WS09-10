#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define A -1
#define B 1
#define PI 3.14159265
#define X (PI/4)

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
                t[i]=(t[j+1]-t[j])/(x[i]-x[j]);
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
    double *t,*a,*x;

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

        printf("n=%d\nx=%f\np=%f\n",n,X,compute_horner(x,a,n));

        free(t);
        free(a);
        free(x);
    }
    else {
        printf("Usage: %s <-l|-t> <n>\n-l Linear distribution\n-t Tschebyscheff distribution\n",argv[0]);
    }

    return EXIT_SUCCESS;
}
