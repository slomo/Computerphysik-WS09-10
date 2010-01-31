#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ANZ 24

/*
 * Usage: If argument given, it will be threated as file with the correct number
 *        of entries;
 */


double avgOfList(double list[],int n){
    int i;
    double avg=0;
    for(i=0;i<n;i++){
        avg += list[i];
    }
    return(avg/n);
}



int main(int argc, char** argv)
{
 
    double xi[ANZ],yi[ANZ];
    
    FILE *file;

    double a, b, sum1=0, sum2=0, xAvg,yAvg;

    int i;

    if(argc==2){
        file = fopen(argv[1],"r");
        for(i=0;i<ANZ;i++){
            fscanf(file,"%lf %lf\n",&xi[i],&yi[i]);
            printf("%lf %lf\n",xi[i],yi[i]);
        }
    }
    else{
        printf("Please specify file to read from\n!");
        return EXIT_SUCCESS;
    }

    xAvg = avgOfList(xi,ANZ); 
    yAvg = avgOfList(yi,ANZ);
    
    for(i=0;i<ANZ;i++){
        sum1 = (xi[i]-xAvg)*(yi[i]-yAvg);
        sum2 = powl((xi[i]-xAvg),2);
    }

    a=sum1/sum2;
    b=yAvg - a * xAvg;

    printf("y=%e*x + %e\n",a,b);

    printf("Age of the universe: %lf Billion years",1/(a/powl(10.0,9)));

    return EXIT_SUCCESS;
}
