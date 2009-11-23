#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 200

double complex f(double l, double n){
    double r    = pow((l - (N/2)),2); 
    double phi  = -2*M_PI*l*n
    return(r*cos(phi) + r*sin(phi)*I);   
}

void distribute_linear(double lower,double upper,double *x, int n)
{
    int i;
    for(i=0;i<n;++i){
        x[i]=lower+i*((upper-lower)/n);
    }
}


void fouier_trans(complex double *h,double complex hFouier,n){
    for(m=1;m<N;m++){
        hFouier[m]=1;
        for(l=1;l<N;l++){
            hFouier[m] += (h[l]*cos(2*l*m*M_PI/N)) + (h[l]*sin(2*l*m*M_PI/N))*I;
            
        }
    }
}

int main(int argc,char *argv[]){

    int m,l;
    double l[N],n[N];
    double complex h[N],hFouier[N][N];
    FILE *fhl, *fhm; 
    
    distribute_linear(0,N-1,n,N);
    distribute_linear(-N/2,N/2,n,N);
    
    for(m=0;m<N;n++){
        
        // vektor h[n] füllen
        // transformieren
        // alle elemente multiplzieren
       
        
        for(n=0;n<N;n++){
            h[n]=f // add brainpower here
        }
    }
    
    fouier_trans(h,hFouier,n);
    


    fhl = fopen("vektor.data","w");
    fhm = fopen("fouier.data","w");

    
    return EXIT_SUCCESS;
}
