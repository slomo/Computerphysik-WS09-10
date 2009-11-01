#include <stdio.h>
#include <stdlib.h>

int fak(int x)
{
    int n,result=1;
    for(n=1;n<=x;++n) {
        result *= n;
    }
    return result;
}

//(n r) = n! / r!(n-r)!
int binom1(int n,int r)
{
    printf("%d, %d, %d\n",fak(n),fak(r),fak(r)*fak(n-r));
    return fak(n) / (fak(r) * fak(n-r));
}

// (n r) = n(n-1)(n-2)...(n-r+1) / r!
int binom2(int n,int r)
{
    int i,result=1;
    for (i=0;i<=r+1;++i) {
        result *=(n-i);
    }
    return result / fak(r);
}


int main(int argc, char* argv[])
{
    if (argc==3) {
        int n = atoi(argv[1]); //get value from agrument 
        int r = atoi(argv[2]); //get value from agrument

        printf("(%d %d) = %d! / %d!(%d-%d)! = %d\n",n,r,n,r,n,r,binom1(n,r));
        printf("(%d %d) = %d(%d-1)(%d-2)...(%d-%d+1) / %d! = %d\n",n,r,n,n,n,n,r,r,binom2(n,r));
    }
    else {
        printf("Usage:\n%s <n> <r>\n",argv[0]);
    }

    return EXIT_SUCCESS;
}
