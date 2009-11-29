#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "diagonalisierung.c"

#define N 200
#define DELTA_X 0.25
#define POTENTIAL_FAK 1 

void distribute_linear(float lower,float upper,float *x, int n){
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

    int m,n,l,rot,i;
    float **gh = matrix(1,N,1,N);
    float **evc = matrix(1,N,1,N);
    float *eva = vector(1,N);
    float mns[N];
    float r,phi,x;
    float complex field, sum;
    FILE *file;
    char* filename = malloc(sizeof(char)*255);

    distribute_linear(-N/2,N/2,mns,N);
    
    // start computation of hamiltonien
    for(m=0;m<N;m++){
        for(n=0;n<N;n++){
            field=2.0/(float)N*powf(M_PI/((float)N*DELTA_X),2);
            
            // this could be replaced by a fouiertransformation
            // so the solution would be more generic and have speedup possibilities
            // due fft
            sum=0;
            for(l=0;l<N;l++){
                r = powf((l-(N/2)),2);
                phi = 2*M_PI*l*(mns[m]-mns[n])/N;
                sum += r*cos(phi) + r*sin(phi)*I; 
            }

            field *= sum;
            field += 0.5*POTENTIAL_FAK*powf(mns[n]*DELTA_X,2) * (n==m ? 1 :0);

            //printf("[%d][%d] %f + %fi \n",m,n,creal(field),cimag(field));

            gh[m+1][n+1] = creal(field); 
        }
    }
    printf("Hamiltonien computed\n");
    
    //computation of the eigenvalues/vectors
    jacobi(gh,N,eva,evc,&rot);
    eigsrt(eva,evc,N);
    printf("Eigenvalues computed\n");
    
    //plot the lowest 5 eigenfunctions to file
    for(i=0;i<5;i++){
        sprintf(filename,"eigenfunction.%d.data",i);
        file = fopen(filename,"w");
        printf("Eigenvalue No. %d: %f\n",i,eva[N-i]);
        for(n=1;n<=200;n++){
            if(n%2==1){
                evc[n][N-i] *= -1;
            }
            fprintf(file,"%d %f\n",n,evc[n][N-i]);
        }
        fclose(file);
    }
    printf("Wrote data to file\n");
    
    return EXIT_SUCCESS;
}
