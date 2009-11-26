#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "diagonalisierung.c"

#define N 200
#define DELTA_X 0.25


void distribute_linear(float lower,float upper,float *x, int n){
    int i;
    for(i=0;i<n;++i){
        x[i]=lower+i*((upper-lower)/n);
    }
}

/*double solve(float *a,float x,int n){
    double p=a[n];
    int i;

    for(i=n-1;i>=0;--i) {
        p=p*(X-x[i])+a[i];
    }
    return p;
}
*/
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

    int m,n,l,rot;
    float **gh = matrix(1,N,1,N);
    float **evc = matrix(1,N,1,N);
    float *eva = vector(1,N);
    float mns[N];
    float r,phi,x;
    float complex field, sum;
    FILE *fhl, *fhm; 

    //gh = (float **) malloc(N*N*sizeof(float));
    //evc = (float **) malloc(N*N*sizeof(float));

    distribute_linear(-N/2,N/2,mns,N);
    
    // start computation of hamiltonien
    for(m=1;m<=N;m++){
        for(n=1;n<=N;n++){
            field=2/N*powf(M_PI/(N*DELTA_X),2);
            
            // this could be replaced by a fouiertransformation
            // so the solution would be more generic and have speeduppossibilitys
            // due fft
            sum=0;
            for(l=0;l<N;l++){
                r = l-powf((N/2),2);
                phi = 2*M_PI*l*(mns[m-1]-mns[n-1])/N;
                
                sum += r*cos(phi) + r*sin(phi)*I; 
            }

            field *= sum;
            field += 0.5*powf(mns[n-1],2) * mns[m-1]-mns[n-1];

            //printf("[%d][%d] %f + %fi \n",m,n,creal(field),cimag(field));

            gh[m][n] = creal(field); 
        }
    }
    printf("Hamiltonien computed\n");
    
    //computation of the eigenvalues/vectors
    jacobi(gh,N,eva,evc,&rot);
    eigsrt(eva,evc,N);

    
    //plot the lowest 5 eigenfunctions to file for [-25,25]
    //fhl = fopen("eigenfunctions.data","w");
    //fhm = fopen("fouier.data","w");
    for(m=N-5;m<=N;m++){
        /*for(x=-25;x<=25;x+=0.25){
            fprintf(fhl,"%f %f",x,compute_horner(
        }*/
        for(n=1;n<=200;n++){
            printf("| %F |",evc[m][n]);
        }
        printf("\n---------------NEXT---------------\n");
    }

   

    return EXIT_SUCCESS;
}
