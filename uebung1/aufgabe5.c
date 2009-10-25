#include <stdio.h>
#include <math.h>

double fak(int n) {
   if(n) return n * fak(n-1);
   return 1;
}

int main(int argc, char* argv[])
{
    int n,x;
    double result1,result2;
    
    for(x=0;x<=10;++x) {
        result1=0;
        for(n=0;n<=5;++n) {
            result1+=(1/fak(n))*pow(x,n);
        }
        result2=exp(x);
        printf("X=%d\n",x);
        printf("  taylor exp: %f\n",result1);
        printf("  math.h exp: %f\n",result2);
        printf("relative err: %e\n",fabs((result1-result2)/result2));
    }
    return 0;
}
