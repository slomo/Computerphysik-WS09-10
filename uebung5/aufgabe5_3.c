#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 200
#define DELTA_X 0.25


void distribute_linear(double lower,double upper,double *x, int n){
    int i;
    for(i=0;i<n;++i){
        x[i]=lower+i*((upper-lower)/n);
    }
}

/*
double complex h(double l, double n){
    double r    = pow((l - (N/2)),2); 
    double phi  = -2*M_PI*l*n;
    return(r*cos(phi) + r*sin(phi)*I);   
}

void fouier_trans(complex double *h,double complex *hFouier,int n){
    int m,l;
    for(m=1;m<N;m++){
        hFouier[m]=1;
        for(l=1;l<N;l++){
            hFouier[m] += (h[l]*cos(2*l*m*M_PI/N)) + (h[l]*sin(2*l*m*M_PI/N))*I;
            
        }
    }
}
*/

int main(int argc,char *argv[]){

    int m,n,l;
    double complex gh[N][N], sum;
    FILE *fhl, *fhm; 
    
    //distribute_linear(0,N-1,n,N);
    //distribute_linear(-N/2,N/2,n,N);
    
    for(m=0;m<N;m++){
        for(n=0;n<N;n++){
            gh[m][n]=2/N*powf(M_PI/(N*DELTA_X),2);
            
            // this could be replaced by a fouiertransformation
            // so the solution would be more generic and have speeduppossibilitys
            // due fft
            sum=0;
            for(l=0;l<N;l++){
                double r = l-(N/2)*(N/2);
                double phi = 2*M_PI*l*(m-n)/N;
                sum += r*cos(phi) + r*sin(phi)*I; 
            }

            gh[m][n] *= sum;
            gh[m][n] += 0.5*powf(n,2);
        }
    }

    

    //fhl = fopen("vektor.data","w");
    //fhm = fopen("fouier.data","w");

    return EXIT_SUCCESS;
}
