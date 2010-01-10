#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rng.h"

void box_muller(double mu, double roh, double *x1, double *x2, double *y1, double *y2, long n) {
    int i;
    for(i=0;i<n;i++) {
        y1[i] = mu + roh*sqrt(-2*log(x1[i])) * cos(2*M_PI*x2[i]);
        y2[i] = mu + roh*sqrt(-2*log(x1[i])) * sin(2*M_PI*x2[i]);
    }
}

int main(int argc, char** argv)
{
    double *x1, *x2, *y1[4], *y2[4],avg1[4],avg2[4],var1[4],var2[4];
    long seed,n,i,j;
    char str[255];
    seed = (long)time(NULL);
    FILE *output1,*output2;
    
    n=(long)pow(10,6);
    
    x1 = malloc(sizeof(double)*n);
    x2 = malloc(sizeof(double)*n);
    y1[0] = malloc(sizeof(double)*n);
    y1[1] = malloc(sizeof(double)*n);
    y1[2] = malloc(sizeof(double)*n);
    y1[3] = malloc(sizeof(double)*n);
    y2[0] = malloc(sizeof(double)*n);
    y2[1] = malloc(sizeof(double)*n);
    y2[2] = malloc(sizeof(double)*n);
    y2[3] = malloc(sizeof(double)*n);
    
    for(i=0;i<n;i++) {
        x1[i] = fabs(ran(&seed));
        x2[i] = fabs(ran(&seed));
    }
    
    //mu = 0  | roh = 0.1
    box_muller(0,0.1,x1,x2,y1[0],y2[0],n);
    //mu = 10  | roh = 0.1
    box_muller(10,0.1,x1,x2,y1[1],y2[1],n);
    //mu = 0  | roh = 1
    box_muller(0,1,x1,x2,y1[2],y2[2],n);
    //mu = 10  | roh = 1
    box_muller(10,1,x1,x2,y1[3],y2[3],n);
    
    // Avarage generation and output
    for(i=0;i<4;i++) {
        sprintf(str,"%ld_y1.out",i);
        output1=fopen(str,"w");
        sprintf(str,"%ld_y2.out",i);
        output2=fopen(str,"w");
        avg1[i] = 0;
        avg2[i] = 0;
        for(j=0;j<n;j++) {
            fprintf(output1,"%f\n",y1[i][j]);
            fprintf(output2,"%f\n",y2[i][j]);
            avg1[i] += y1[i][j];
            avg2[i] += y2[i][j];
        }
        avg1[i] /= n;
        avg2[i] /= n;
        printf("\ny1 %ld avarage: %f\n",i,avg1[i]);
        printf("y2 %ld avarage: %f\n",i,avg2[i]);
        free(output1);
        free(output2);
    }

    return EXIT_SUCCESS;
}
