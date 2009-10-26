#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *args[]){
    
    int limit,n;
    FILE* out = malloc(sizeof(struct file));
    double sumUp=0,sumDown=0;

    limit = atoi(args[1]); // read n from argument 1
    //Sup
    for(n=1;n<=limit;n++){
        sumUp +=  1/n;
    }

    //Sdown
    for(n=limit;n>0;n++){
        sumUp +=  1/n;
    }

    out = fopen("output.tmp","w");
    fprintf(out,"Sup: %E\nSdown: %E\n",sumUp,sumDown);
    fprintf(stdout,"Results have been writen to file");

    fclose(out);
    return EXIT_SUCCESS;
}
