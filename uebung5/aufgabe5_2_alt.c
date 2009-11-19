#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>

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

    int m;
    double h[N],x[N];
 
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    FILE *fhl, *fhm; 

    distribute_linear((-4*M_PI),(4*M_PI),x,N);

    for(m=0;m<N;m++){
        h[m] = f(x[m]);
        in[m] = h[m];
    }

    fhl = fopen("vektor.data","w");
    fhm = fopen("fouier.data","w");

    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);

    for(m=1;m<N;m++){
        printf("x:%f \thl:%f \tHm:%f + %fi\n",x[m],h[m],creal(out[m]),cimag(out[m]));
        
        fprintf(fhl,"%f %f\n",x[m],h[m]);
        //fprintf(fhm,"%f {%f,%f}\n",x[m],creal(hFouier[m]),cimag(hFouier[m]));
        fprintf(fhm,"%f %f\n",x[m],creal(out[m]));

    }
    fftw_free(in);
    fftw_free(out);
    
    return EXIT_SUCCESS;
}
