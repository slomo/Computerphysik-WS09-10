#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

int main(int argc, char* argv[])
{
    int n,i;
    double probe,result,faktor,err,tmp;
    double *t,*a,*x;

    FILE *fErr, *fRes;
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

        // computing polynomial
        distribute_linear(x,n);
        compute_polynomial(x,t,n,a);
        
        // computing max error
        faktor=1;
        for(i;i<=n;i++){
            faktor *= (1 + 2*i);
        }
        faktor *= 0.25 * powf(-1,n);
        faktor /= fak(n);
        err = 0;
        for(probe=A+(X1/PROBEC);probe<=X1;probe+=(X1/PROBEC)){
            tmp = faktor * powf(probe,(-(2.0*n-1.0)/2.0));
            if(tmp > err){
                err = tmp;
            }
        }

        for(probe=A+(X1/PROBEC);probe<=X1;probe+=(X1/PROBEC)){
            // whar goes here????
        }


        for(probe=A+(X1/PROBEC);probe<=X1;probe+=(X1/PROBEC)){
            result = compute_horner(probe,x,a,n);
            fprintf(fRes,"%.20E %.20E\r\n",probe,result);
            fprintf(fErr,"%.20E %.20E\r\n",probe,fabs(result-f(probe)));
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
