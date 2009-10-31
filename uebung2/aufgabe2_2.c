#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP 10
#define LIMIT powl(10,9)

/* 
 * We took the formular for the expected value from wikipedia.
 * http://en.wikipedia.org/wiki/Harmonic_series_(mathematics)
 *
 * The constant value is an approximation of the Euler–Mascheroni constant.
 *
 */

int main(int argc,char *args[]){
    
    long long int i,down,up;
    FILE *f_sup,*f_sdown,*f_div;
    float sumUp,sumDown;

    f_sup   = fopen("aufgabe2_3.sup.data","w");
    f_sdown = fopen("aufgabe2_3.sdown.data","w");
    f_div   = fopen("aufgabe2_3.div.data","w");

    for(i=10;i<LIMIT;i *=10){
        sumUp=0;
        sumDown=0;

        for(down=i;down>0;down--){
            sumDown +=  1/((double) down);
        }
        for(up=0;up<i;up++){
            sumUp +=  1/(up+1.0);
        }
        
        fprintf(f_sup,"%lld %.20E\r\n",i,sumUp);
        fprintf(f_sdown,"%lld %.20E\r\n",i,sumDown);
        fprintf(f_div,"%lld %.20E\r\n",i
                ,abs(sumUp-sumDown)/(sumUp+sumDown));
        
        fprintf(stdout,"[%lld]\r\n\
            \tSup: \t%.20E\r\n\
            \tSdown: \t%.20E\r\n\
            \tExp: \t%.9E\r\n"
            ,i,sumUp,sumDown,log(i)+0.5772156649);
        fprintf(stdout,"Results have been writen to file\r\n");
    }
    

    fclose(f_sup);
    fclose(f_sdown);
    fclose(f_div);
    return EXIT_SUCCESS;
}

/*
 * The above Implemantation is not the utmost performant implemantation,
 * but it should be best to show the desired effect, even if the differences
 * between those two resaults are not signifcant (that should be caused by the 
 * usage of double precission.
 */


