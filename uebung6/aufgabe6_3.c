#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1 
#define FALSE 0
#define N 200
#define LEVELS 5
#define PRES 0.00001

int fak[LEVELS+1];

double h_n(int n, double x) {
    int k1,k2;
    double result;
    if(n==0) {
        return 1;
    }
    else if(n==1) {
        return 2.0*x;
    }
    else {
        
        result = powf(-1,n);
        for(k2=0;2*k2<=n;k2++) {
            k1=n-2*k2;
            result += fak[n]/(fak[k1]*fak[k2]) * powf(-1,k1+k2) * powf(2*x,k1);
        }
        
        return result;
    }
}

double phi(int n, double x) {

    //double m=1,w=1,h=1;
    if (n==0) {
        //return powf(m*w/(M_PI*h),0.25) * exp(-0.5*m*w/h*x*x);
        return powf(1/(M_PI),0.25) * exp(-0.5*x*x);
    }
    else {
        //return powf(m*w/(M_PI*h),0.25) * (1.0/sqrt(pow(2,n)*fak[n]))* h_n(n,sqrt(m*w/h)*x) * exp(-0.5*m*w/h*x*x);
        return powf(1/(M_PI),0.25) * (1.0/sqrt(pow(2,n)*fak[n]))* h_n(n,x) * exp(-0.5*x*x);
    }
}

double phi_2(int n, double x) {
    return powf(phi(n,x),2);
}

void distribute_linear(double lower,double upper,double *x, int n) {
    int i;
    for(i=0;i<n;++i){
        x[i]=lower+i*((upper-lower)/n);
    }
}

// Constrain a < b
double intergrate_homer(double a,double b,int n,double (*f)(int,double), int j){
    double i;
    double h = (b-a)/(double)n;
    double sum = 0;
    char even = TRUE;

    // could be done more iffecient in array with int i, but needs more mem
    sum += f(j,a) + f(j,b);
    for(i=a+h;i<b;i+=h){
        if(even){
            sum += 4.0*f(j,i); 
        } 
        else{
            sum += 2.0*f(j,i);
        }
        even = !even;
    }

    return(sum*(h/3.0));
}

int main(int argc,char *argv[]) {
    int i,j,steps;
    double probes[N],a,result,oldresult;
    FILE *fphi;
    char filename[50];
    
    //Calc faks
    fak[0]=1;
    for(i=1;i<=LEVELS;i++) {
        fak[i]=fak[i-1]*i;
    }
    
    distribute_linear(-5,5,probes,N);
    
    for(j=0;j<=LEVELS;j++) {
        sprintf(filename,"phi_n%d.data",j);
        fphi=fopen(filename,"w");
        for(i=0;i<N;i++){
            fprintf(fphi,"%f %f\n",probes[i],phi(j,probes[i]));
        }
        fclose(fphi);
        
        a=sqrt(2*j+1);
        result=intergrate_homer(-a,a,4,phi_2,j);
        oldresult=intergrate_homer(-a,a,8,phi_2,j);
        steps=16;
        while(fabs(oldresult-result) > PRES) {
            oldresult=result;
            result=intergrate_homer(-a,a,steps,phi_2,j);
            steps *= 2;
        }
        printf("Result for n=%d: %f => chance to be out of bounds: %f\n",j,result,1-result);
        
    }
    
    return EXIT_SUCCESS;
}
