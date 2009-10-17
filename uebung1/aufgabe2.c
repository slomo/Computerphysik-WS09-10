#include<stdio.h>


double mAcc(int alpha){
    double eps=1;
    while(eps+alpha != alpha){
        eps /= 2;

    }
    return(eps*2);
}

int main(int argc,int args[]){
    int i;
    double alphas[]= {1,1e-4,10e11};

    for(i=0;i<3;i++){
        fprintf(stdout,"Machine accurracy for alpha = %E is %E\r\n",
                alphas[i],mAcc(alphas[i]));
    }
}




