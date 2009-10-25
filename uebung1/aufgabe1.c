#include <stdio.h>

int main(int argc,char *args[]) {
    fprintf(stdout,"Size of some datatypes\r\n");
    fprintf(stdout,"=================================================\r\n");
    fprintf(stdout,"\t character: \t %ld byte\r\n",sizeof(char));
    fprintf(stdout,"\t short int: \t %ld byte\r\n",sizeof(short));
    fprintf(stdout,"\t interger: \t %ld byte\r\n",sizeof(int));
    fprintf(stdout,"\t double: \t %ld byte\r\n",sizeof(double));

    return 0;
}
