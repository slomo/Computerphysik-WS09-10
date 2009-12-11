#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1 
#define FALSE 0

double f(double x){
    return(sqrt(1-powf(x,2)));
}

double g(double x){
    return(1/(1+powf(x,2)));
}

void distribute_linear(double lower,double upper,double *x, int n){
    int i;
    for(i=0;i<n;++i){
        x[i]=lower+i*((upper-lower)/n);
    }
}

// Constraint: a < b
double intergrate_trapezoidal(double a,double b,int n,double (*f)(double)){
    double i;
    double h = (b-a)/(double)n;
    double sum = 0;

    // could be done more iffecient in array with int i, but needs more mem
    sum += 0.5 * (f(a) + f(b));
    for(i=a+h;i<b;i+=h){
        sum += f(i); 
    }

    return(sum*h);
}

// Constrain a < b
double intergrate_homer(double a,double b,int n,double (*f)(double)){
    double i;
    double h = (b-a)/(double)n;
    double sum = 0;
    char even = TRUE;

    // could be done more iffecient in array with int i, but needs more mem
    sum += f(a) + f(b);
    for(i=a+h;i<b;i+=h){
        if(even){
            sum += 4.0*f(i); 
        } 
        else{
            sum += 2.0*f(i);
        }
        even = !even;
    }

    return(sum*(h/3.0));
}

int main(int argc,char *argv[]){
    int i;
    double result;
    printf("For the 1st function:\n");
    for(i=10;i<=1000;i*=10){
        result = intergrate_trapezoidal(0,1,i,f)*4;
        printf("\tWith trapezoidal rule and %d intervals: %f\terror: %f%%\n",i,
            result,(result/M_PI-1)*100);
    }

    for(i=10;i<=1000;i*=10){
        result = intergrate_homer(0,1,i,f)*4;
        printf("\tWith simpson rule and %d intervals: %f\t\terror: %f%%\n",i,
            result,(result/M_PI-1)*100);
    }

    
    printf("For the 2nd function:\n");
    for(i=10;i<=1000;i*=10){
        result = intergrate_trapezoidal(0,1,i,f)*4;
        printf("\tWith trapezoidal rule and %d intervals: %f\terror: %f%%\n",i,
             result,(result/M_PI-1)*100);
    }

    for(i=10;i<=1000;i*=10){
        result = intergrate_homer(0,1,i,g)*4;
        printf("\tWith simpson rule and %d intervals: %f\t\terror: %f%%\n",i,
             result,(result/M_PI-1)*100);
    }

    return EXIT_SUCCESS;
}
