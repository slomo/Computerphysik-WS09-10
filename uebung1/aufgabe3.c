#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *args[]) {
    char* string = malloc(sizeof(char)*81);
    int i;

    fscanf(stdin,"%80s",string);
    
    for(i=strlen(string);i>=0;i--){
        putc(string[i],stdout);
    }
    putc('\n',stdout);

    return 0;
}
