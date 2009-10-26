#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP 10
#define LIMIT pow(10,8)

int main(int argc,char *args[]){
    
    int down=pow(10,8),up=1,count=10;
    FILE* out;
    double sumUp=0,sumDown=0;

    out = fopen("output.tmp","a");
    
    while(down > 0){
        sumUp +=  1/((double) up);
        sumDown +=  1/((double) down);
        
        up ++;
        down --;
        if(up==count){
            fprintf(out,"[%d][%d]\r\n\
                    \tSup: %E\r\n\
                    \tSdown: %E\r\n"
                ,up,down,sumUp,sumDown);
            fprintf(stdout,"Results have been writen to file\r\n");
            count *= 10;
        }
    }
    fprintf(out,"\tExpected: %E\r\n",log(up)+0.5772156649);

    fclose(out);
    return EXIT_SUCCESS;
}
