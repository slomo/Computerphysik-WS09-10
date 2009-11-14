#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define A 0.0
#define B 1.0
#define PROBEC 100.0
#define PI 3.14159265
#define X1 B/n

/*
 * Wee took some parts auf that code from our solution of taks 2 on 
 * assignment 3. 
 */


double f(double x)
{
    return (sqrt(x));
}

double fak(double x){
    int i;
    double result = 1;
    for(i=1;i<=x;i++){
        result *= i;
    }
    return(result);
}


void distribute_linear(double *x, int n)
{
    int i;
    for(i=1;i<=n;++i){
        x[i-1]=A+i*((B-A)/n);
    }
}


void compute_polynomial(double *x,double *t,int n,double *a){
    int i,j;

    for(i=0;i<n;++i) {
        t[i]=f(x[i]);
        if(i>=1) {
            for(j=i-1;j>=0;--j) {
                t[j]=(t[j+1]-t[j])/(x[i]-x[j]);
            }
        }
            a[i]=t[0];
    }
}


double compute_horner(double probe,double *x,double *a,int n){
    // modified caused by smaller interval (first value is not included) 
    double p=a[n-1];
    int i;

    for(i=n-2;i>=0;--i){
        p=p*(probe-x[i])+a[i];
    }
    return p;
}

double compute_faktor(double s, double e,int n){
    // get faktor (see .pdf for additional info)
    double max=-DBL_MAX,tmp=max,xi;
    double faktor = 1;
    int i;
    faktor = (-1) * ((n+1)%2); // efficient way for (-1)^n+1
    for(i=1;i<=(n+1);i++){
        faktor *= 1.0-(3.0/(2.0*i));
    }
    
    for(xi=s;xi<=e;xi=+(X1/PROBEC)){
        tmp = faktor * pow(xi,(n+1)-0.5);
        if(tmp > max){
            max = tmp;
        }
    }

    return faktor;
}

double compute_max_err(double s,double tilde,double faktor,int n){
    double xi;

    for(xi=s;xi<tilde;xi=+(X1/PROBEC)){
        faktor*=xi;
    }
    return(faktor);
}

int main(int argc, char* argv[])
{
    int n;
    double probe,result,faktor;
    double *t,*a,*x;

    FILE *fErr, *fRes, *fMaxError;
    char* filename;

    if(argc==2) {

        // perparation
        n = atoi(argv[1]);
        
        t = malloc((sizeof(double)*(n)));
        a = malloc((sizeof(double)*(n)));
        x = malloc((sizeof(double)*(n)));
        
        if(0<n && n<100){
            filename = malloc(sizeof("xxx.ZZ.dat"));
        }
        else{
            printf("Usage: %s <n>, where 0<n<100\r\n",argv[0]);
        }

        strcat(filename,"err.");
        strcat(filename,argv[1]);
        strcat(filename,".dat");
        fErr = fopen(filename,"w");

        filename[0] = '\0';
        strcat(filename,"res.");
        strcat(filename,argv[1]);
        strcat(filename,".dat");
        fRes = fopen(filename,"w");

        filename[0] = '\0';
        strcat(filename,"maxError.");
        strcat(filename,argv[1]);
        strcat(filename,".dat");
        fMaxError = fopen(filename,"w");
        
        // computing polynomial
        distribute_linear(x,n);
        compute_polynomial(x,t,n,a);
        
        // computing maax error
        faktor = compute_faktor(A+(X1/PROBEC),X1,n);

        for(probe=A+(X1/PROBEC);probe<=X1;probe+=(X1/PROBEC)){
            result = compute_horner(probe,x,a,n);
            fprintf(fRes,"%.20E %.20E\r\n",probe,result);
            fprintf(fErr,"%.20E %.20E\r\n",probe,fabs(result-f(probe)));
            fprintf(fMaxError,"%.20E %.20E\r\n",probe,
                    compute_max_err(A+(X1/PROBEC),probe,faktor,n));
        }
        for(;probe<=B;probe+=(X1/PROBEC)){
            fprintf(fRes,"%.20E %.20E\r\n",probe,result);
        }
        

        fclose(fRes);
        fclose(fErr);
        
        free(t);
        free(a);
        free(x);
    }
    else {
        printf("Usage: %s <n> output is written to lin.data and tsc.data \r\n",
            argv[0]);
    }
    return EXIT_SUCCESS;
}
