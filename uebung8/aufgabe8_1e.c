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

void zero_stats(long *in, long n) {
	int i;
	for(i=0;i<n;i++) {
		in[i]=0;
	}
}

void do_stats(double mu, double roh, double *in, long *out, long n, long sampeles) {
    double range,sample,j;
    int i,index;
    range = 2.0*5.0*roh;
    sample = range/sampeles;
    for(i=0;i<n;i++) {
		index=0;
        for(j=mu-5*roh;j<=mu+5*roh;j+=sample) {
            if((in[i] >= j) && (in[i] < j+sample)) {
				if(index<sampeles) {
					out[index]++;
				}
			} 
			index++;
		}
    }
}

int main(int argc, char** argv)
{
    double *x1, *x2, *y1[4], *y2[4],avg1[4],avg2[4],var1[4],var2[4],x,mu,roh;
    long seed,n,i,j,*stats;
    char str[255];
    seed = (long)time(NULL);
    FILE *output;
    
    n=(long)pow(10,6);
    
    stats = malloc(sizeof(long)*100);
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
        avg1[i] = 0;
        avg2[i] = 0;
        var1[i] = 0;
        var2[i] = 0;
        for(j=0;j<n;j++) {
            avg1[i] += y1[i][j];
            avg2[i] += y2[i][j];
            switch (i) {
				case 0:
				case 2:
					var1[i] += pow(y1[i][j],2);
					var2[i] += pow(y2[i][j],2);
					break;
				case 1:
				case 3:
					var1[i] += pow(y1[i][j]-10,2);
					var2[i] += pow(y2[i][j]-10,2);
					break;
			}
        }
        avg1[i] /= n;
        avg2[i] /= n;
        var1[i] *= 1.0/(n-1.0);
        var2[i] *= 1.0/(n-1.0);
        printf("\ny1 %ld avarage: %f / var: %f\n",i,avg1[i],var1[i]);
        printf("y2 %ld avarage: %f / var: %f\n",i,avg2[i],var2[i]);        
    }
    
    for(j=0;j<4;j++){
		switch(j) {
			case 0:
				mu=0;
				roh=0.1;
				break;
			case 1:
				mu=10;
				roh=0.1;
				break;
			case 2:
				mu=0;
				roh=1;
				break;
			case 3:
				mu=10;
				roh=1;
				break;
		}
		
		sprintf(str,"%ld_y1.out",j);
		output=fopen(str,"w");
		zero_stats(stats,100);
		do_stats(mu,roh,y1[j],stats,n,100);
		x=mu-5*roh;
		for(i=0;i<100;i++) {
			fprintf(output,"%f %ld\n",x,stats[i]);
			x+=(2.0*5.0*roh)/100.0;
		}
		fclose(output);
		
		sprintf(str,"%ld_y2.out",j);
		output=fopen(str,"w");
		zero_stats(stats,100);
		do_stats(mu,roh,y2[j],stats,n,100);
		x=mu-5*roh;
		for(i=0;i<100;i++) {
			fprintf(output,"%f %ld\n",x,stats[i]);
			x+=(2.0*5.0*roh)/100.0;
		}
		fclose(output);
	}

    
    return EXIT_SUCCESS;
}
