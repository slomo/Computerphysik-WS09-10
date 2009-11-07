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

double compute_horner(double probe,double *x,double *a,int n){
    double p=a[n];
    int i;

    for(i=n-1;i>=0;--i) {
        p=p*(probe-x[i])+a[i];
    }
    return p;
}

int main(int argc, char* argv[])
{
    int n;
    double probe;
    double *t,*a,*x;

    FILE *file;
    char* filename;

    if(argc==2) {

        n = atoi(argv[1]);
        
        t = malloc((sizeof(double)*(n+1)));
        a = malloc((sizeof(double)*(n+1)));
        x = malloc((sizeof(double)*(n+1)));
        
        if(0<n && n<100){
            filename = malloc(sizeof("xxx.ZZ.dat"));
        }
        else{
            printf("Usage: %s <n> while 0<n<100\r\n",argv[0]);
        }

        // computing results for linear distribition
        distribute_linear(x,n);
        compute_polynomial(x,t,n,a);

        strcat(filename,"lin.");
        strcat(filename,argv[1]);
        strcat(filename,".dat");

        file = fopen(filename,"w");
        // and write them to file
        for(probe=-1;probe<=1;probe+=(1.0/250.0)){
            fprintf(file,"%.20E %.20E\r\n",probe,compute_horner(probe,x,a,n));
        }
        fclose(file);
        

        // computing results for tschebyscheff distribition
        distribute_tschebyscheff(x,n);
        compute_polynomial(x,t,n,a);

        filename[0] = '\0';
        strcat(filename,"tsc.");
        strcat(filename,argv[1]);
        strcat(filename,".dat");
        
        file = fopen(filename,"w");
        // and write them to file
        for(probe=-1;probe<=1;probe+=(1.0/250.0)){
            fprintf(file,"%.20E %.20E\r\n",probe,compute_horner(probe,x,a,n));
        }
        fclose(file);


        free(t);
        free(a);
        free(x);
    }
    else {
        printf("Usage: %s <n> output is written to lin.data and tsc.data \r\n",argv[0]);
    }

    return EXIT_SUCCESS;
}
