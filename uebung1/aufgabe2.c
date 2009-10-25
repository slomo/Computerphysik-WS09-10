#include <stdio.h>

double mAcc(int alpha){
    double eps=1;
    while(eps+alpha != alpha){
        eps /= 2;

    }
    return (eps*2);
}

int main(int arg,char* args[]){
    int i;
    double alphas[]= {1,1e-4,10e11};

    for(i=0;i<3;i++){
        fprintf(stdout,"Machine accurracy for alpha = %E is %E\r\n",
                alphas[i],mAcc(alphas[i]));
    }

    return 0;
}

/*
 * Anwser to the Questions:
 *
 * The machine accuracy discribes the smallest presentable difference 
 * between alpha and an other value. If we don't divde epsilon by two,
 * it could be possible the we have to stop earlier, so we won't have
 * the exact accuracy.
 */



