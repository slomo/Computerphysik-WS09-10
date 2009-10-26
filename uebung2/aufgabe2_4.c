#include <stdio.h>
#include <stdlib.h>

int fak_int(int x)
{
    int n,result=1;
    for(n=1;n<=x;++n) {
        result *= n;
    }
    return result;
}

float fak_float(float x)
{
    float n,result=1;
    for(n=1;n<=x;++n) {
        result *= n;
    }
    return result;
}

double fak_double(double x)
{
    double n,result=1;
    for(n=1;n<=x;++n) {
        result *= n;
    }
    return result;
}


int main(int agrc, char* argv[])
{
    printf("Fak(12) useing Integer: %d\n",fak_int(12));          //max=12
    printf("Fak(13) useing Integer: %d\n  -> overflow should be %.0f\n\n",fak_int(13),fak_float(13));      //overflow
    
    printf("Fak(34) useing Float  : %.0f\n",fak_float(34));      //max=34
    printf("Fak(35) useing Float  : %.0f\n\n",fak_float(35));    //equals inf

    printf("Fak(170) useing Double : %.0f\n",fak_double(170));   //max=170  
    printf("Fak(171) useing Double : %.0f\n\n",fak_double(171)); //equals inf  
   
    return EXIT_SUCCESS;
}
