#include <stdio.h>
#include <math.h>

#define MAXSAMPELS 5
// this programm has to be linked with -lm options

int main(int argc,char *args[]){
    double avg=0,stddev=0,set[4];
    int i;
    
    fprintf(stdout,"Please enter your sampels:\r\n");
    for(i=0;i<MAXSAMPELS;i++){
        fprintf(stdout,"Sample No. %d: ",(i+1));
        fscanf(stdin,"%lf",(set+i));
    }
    
    // compute average
    for(i=MAXSAMPELS;i>=0;i--){
        avg += set[i];
    }
    avg /= MAXSAMPELS;
    fprintf(stdout,"The average is: %e\r\n",avg);

    // compute standard deviation
    for(i=0;i<5;i++){
        stddev += pow((set[i] - avg),2);
    }
    stddev /= MAXSAMPELS-1;
    stddev = sqrt(stddev);
    fprintf(stdout,"The standard deviation is: %e\r\n",stddev);
    return 0;
}
