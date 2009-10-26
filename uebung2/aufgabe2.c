#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP 10
#define LIMIT powl(10,9)

/* 
 * We took the formular for the exact value from wikipedia.
 * http://en.wikipedia.org/wiki/Harmonic_series_(mathematics)
 *
 * The constant value is an approximation of the Euler–Mascheroni constant.
 *
 */

int main(int argc,char *args[]){
    
    long long int i,down,up;
    FILE* out;
    double sumUp,sumDown;

    out = fopen("output.tmp","w");
    
    for(i=10;i<LIMIT;i *=10){
        sumUp=0;
        sumDown=0;

        for(down=i;down>0;down --){
            sumDown +=  1/((double) down);
        }
        for(up=0;up<i;up++){
            sumUp +=  1/(up+1.0);
        }
        
        fprintf(out,"[%lld][%lld]\r\n\
            \tSup: \t%.9E\r\n\
            \tSdown: \t%.9E\r\n\
            \tExact: \t%.9E\r\n"
            ,up,down,sumUp,sumDown,log(i)+0.5772156649);
        fprintf(stdout,"Results have been writen to file\r\n");
    }
    

    fclose(out);
    return EXIT_SUCCESS;
}
