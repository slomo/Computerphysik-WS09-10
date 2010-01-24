#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ACCU powl(10,-1)


/*
 * Compute the euklidic norm of the given vector
 */
double euklid(double vector[], int dim){
    double sum=0;
    int i;
    for(i=0;i<dim;i++){
        sum+= vector[i]*vector[i];
    }
    printf("%lf",sum);
    return(sqrt(sum));
}

/*
 * One iteration for the jacobi method, to solve LES
 */
void iterate(double matrix[][4],double vector[],double last[],double next[],int dim){
    
    double sum;
    int i,j;

    for(i=0;i<dim;i++){
        sum=0;
        for(j=0;j<dim;j++){
            if(j!=i){
                sum += matrix[i][j] + last[j];
            }
        }
        next[i] = (vector[i]-sum) / matrix[i][i];
    }
}

/*
 * Test if quality is engough.
 *
 * return:  0 - yes
 *         -1 - no
 */
int goodQual(double matrix[][4],double vector[],double x[],int dim){

    double res[4];
    int i,j;

    for(i=0;i<4;i++){
        res[i]=0;
        for(j=0;j<4;j++){
            res[i] += matrix[i][j]*x[i];
        }
        res[i] -= vector[i];
    }

    if(euklid(res,dim) <= ACCU){
        return 0;
    }
    else{
        return -1;
    }
    
}


int main(int argc, char** argv)
{
    //double matrix [4][4];
    double b[4]=
        { -7.53,  6.06,  8.05, -8.10};
    double end[4], start[4], *xChange, *xNow=start, *xPast=end;
    double matrix[4][4] = {
        {  6.22,  1.42, -1.72,  1.91},
        {  1.44,  5.33,  1.11, -1.82},
        {  1.59, -1.23, -5.24, -1.42},
        {  1.75, -1.69,  1.57,  6.55}
    };

    int i,j,t=0;
    
    //while(goodQual(matrix,b,xNow,4)!=0){
    
    while(t<200){
        t++;
        iterate(matrix,b,xPast,xNow,4);

        xChange = xNow;
        xNow = xPast;
        xPast = xChange;

        printf(".");
    }

    printf("\r\nResult\r\n");

    for(i=0;i<4;i++){
        printf("| %lf | \r\n",xNow[i]);
    }

    return EXIT_SUCCESS;
}
