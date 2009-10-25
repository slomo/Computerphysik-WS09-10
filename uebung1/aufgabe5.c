#include <stdio.h>
#include <math.h>

double fak(int n) {
   if(n) return n * fak(n-1);
   return 1;
}

int main(int argc, char* argv[])
{
    int n,x;
    double result1,result2,relErr;
    
    for(x=0;x<=10;++x) {
        result1=0;
        for(n=0;n<=5;++n) {
            result1+=(1/fak(n))*pow(x,n);
        }
        result2=exp(x);
        relErr=(result1-result2)/result2;
        printf("X=%d\n",x);
        printf("  taylor exp: %e\r\n",result1);
        printf("  math.h exp: %e\r\n",result2);
        printf("relative err: %e (equals %.2f %%) \r\n",relErr,relErr*100);
    }
    return 0;
}
