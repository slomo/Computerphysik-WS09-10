#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ACCU pow(10,-6)


// the function it self
double f(double x) {
    return(powl(x,10)-45*powl(x,8)+630*powl(x,6)-3150*powl(x,4)+4725*powl(x,2)-945);   
    //return(x*x*x);
}

// first derivativ of the function (calcultated manully)
double fd(double x) {
    //return(10*powl(x,9)-360*powl(x,7)+3780*powl(x,5)-12600*powl(x,3)+9450*x);   
    //return(3*x*x);
   double dx = ACCU*2;
   return((f(x+dx)-f(x))/dx);
}

// this function does the computation need for the newton algorithm
double wheel(double(*f)(double), double(fd)(double), double guess) {
    
    printf("Starting caluculation: ");  
    double value = f(guess);

    // while our guess is not accurate enough, we have do do an other "guess"
    while(fabs(value) > ACCU){
        
        value = f(guess);
        guess = guess - (value/fd(guess));
        printf(".");

    }

    printf(" >> DONE \r\n");

    return guess;
}

int main(int argc, char** argv)
{
    int i,seedc;
    double seeds[10]; // our initial guesses are stored here
    

    if(argc ==1){
        // computed seeds
        // seeds were guessed (could be computed with brute force)
        seeds[0] = -5;
        seeds[1] = -3.5;
        seeds[2] = -3;
        seeds[3] = -1.9;
        seeds[4] = -2;

        seeds[9] = 5;
        seeds[8] = 3.5;
        seeds[7] = 3;
        seeds[6] = 1.9;
        seeds[5] = 2;

        seedc = 10; 
    }
    else{
        // this code reads the seeds from the parameters
        for(i=0;i<argc-1;i++){
            sscanf(argv[i+1],"%lf",&seeds[i]);
        }
        seedc = argc-1;
    }

    for(i=0;i<seedc;i++){
        
        // compute and write result to stdout
        seeds[i]=wheel(f,fd,seeds[i]);
        printf("root %d -> f(%lf)=%lf \r\n",i,seeds[i],f(seeds[i]));
    }

    return EXIT_SUCCESS;
}
