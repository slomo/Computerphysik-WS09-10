#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *args[]) {
    char* string = malloc(sizeof(char)*81);
    int i;

    fscanf(stdin,"%80s",string);
    
    for(i=80;i>=0;i--){
        putc(string[i],stdout);
    }
    putc('\n',stdout);

    return 0;
}
