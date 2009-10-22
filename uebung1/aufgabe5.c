#include <stdio.h>
#include <math.h>

double fak(long n) {
   if(n) return n * fak(n-1);
   return 1;
}

int main(int argc, char* argv[])
{
    int n,x;
    double result1,result2;
    
    for(x=0;x<=10;++x) {
        result1=0;
        for(n=0;n<=6;++n) {
            result1+=(1/fak(n))*pow(x,n);
            printf("1/n! %f\n",(1 / fak(n)));
            printf("x^n  %f\n",pow(x,n));
            printf("=    %f\n",result1);
        }
        result2=exp(x);
        printf("X=%d\n",x);
        printf("  taylor exp: %f\n",result1);
        printf("  math.h exp: %f\n",result2);
        printf("relative err: %f\n",result1-result2); //FIXME: I think this needs a more correct error calculation
    }
    return 0;
}
