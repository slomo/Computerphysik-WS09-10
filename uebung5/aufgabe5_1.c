#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define A -5.0
#define B 5.0
#define N 4

double f(double x)
{
    return 5/(1+25*x*x);
}

void distribute_linear(double *x, int n)
{
    int i;
    for(i=0;i<n;++i){
        x[i]=A+i*((B-A)/n);
    }
}

int main(int argc, char* argv[])
{
    double probes[100],a[4][4],x[4]={-2,-1,1,2},result,y[4],h[4];
    int i,j=0;
    FILE *fallout,*fsollout,*ferrout;

    fallout = fopen("aufgabe5_1.out","w");
    fsollout = fopen("aufgabe5_1_soll.out","w");
    ferrout = fopen("aufgabe5_1_err.out","w");

    distribute_linear(probes,100);

    /* | 2.00 0.00 0.00 0.00 |  |M0|  |0.000000|
     * | 0.33 2.00 0.67 0.00 |  |M1|  |-0.285605|
     * | 0.00 0.67 2.00 0.33 |  |M2|  |-0.285605|
     * | 0.00 0.00 0.00 2.00 |  |M3|  |0.000000|
     * 
     * Solution M0 = 0, M1 = -0.107101875, M2 = -0.107101875, M3 = 0
     */ 
    double M[4]={0,-0.107101875,-0.107101875,0};
    
    for(i=0;i<N;i++) {
        y[i]=f(x[i]);
        h[i]=x[i]-x[i-1];
    }

    for(i=0;i<=2;i++) {
        a[i][0]=y[i];
        a[i][1]=(y[i+1]-y[i])/h[i+1] - (2*M[i]+M[i+1])/6 * h[i+1];
        a[i][2]=M[i]/2;
        a[i][3]=(M[i+1]-M[i])/(6*h[i+1]);
    }

    for(i=0;i<100;i++) {
        if ((probes[i] == -1) || (probes[i] == 1)) {
            j++;
        }
        result=a[j][0]+a[j][1]*(probes[i]-x[j])+a[j][2]*pow((probes[i]-x[j]),2)+a[j][3]*pow((probes[i]-x[j]),3);
        fprintf(fallout,"%f %f\n",probes[i],result);
        fprintf(fsollout,"%f %f\n",probes[i],f(probes[i]));
        fprintf(ferrout,"%f %f\n",probes[i],result-f(probes[i]));
    }

    fclose(fallout);
    fclose(fsollout);
    fclose(ferrout);

return EXIT_SUCCESS;
}
