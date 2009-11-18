#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100

double f(double x){
    return(sin(x/2)+(sin(x)*sin(x)));   
}

void distribute_linear(double lower,double upper,double *x, int n)
{
    int i;
    for(i=0;i<=n;++i){
        x[i]=lower+i*((upper-lower)/n);
    }
}

int main(int argc,char *argv[]){

    int m,l;
    double h[N],x[N];
    double complex hFouier[N];
    
    FILE *fhl, *fhm; 

    distribute_linear((-4*M_PI),(4*M_PI),x,N);

    for(l=0;l<N;l++){
        h[l] = f(x[l]);
    }

    fhl = fopen("vektor.data","w");
    fhm = fopen("fouier.data","w");

    for(m=1;m<N;m++){
        hFouier[m]=1;
        for(l=1;l<N;l++){
            hFouier[m] += (h[l]*cos(2*l*m*M_PI/N)) + (h[l]*sin(2*l*m*M_PI/N))*I;
            
        }

        printf("x:%f \thl:%f \tHm:%f + %fi\n",x[m],h[m]
                ,creal(hFouier[m]),cimag(hFouier[m]));
        
        fprintf(fhl,"%f %f\n",x[m],h[m]);
        //fprintf(fhm,"%f {%f,%f}\n",x[m],creal(hFouier[m]),cimag(hFouier[m]));
        fprintf(fhm,"%f %f\n",x[m],creal(hFouier[m]));

    }
    
    return EXIT_SUCCESS;
}
