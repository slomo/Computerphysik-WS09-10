#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEST

void printSquareMatrixandVector(double matrix[][4], double vector[], int count) {
    int i,j;
    for(i=0;i<count;i++){
        printf("|");
        for(j=0;j<count;j++){
            printf(" %lf ",matrix[i][j]);
        }
        printf("|\t| %lf | \r\n",vector[i]);
    }
    printf("\n");
}

/*
 * Seeks first non-zero value in colum <col>, below row<row>.
 * Than it swaps the part from <col> to <dim>  of this row with 
 * the given row <row>
 *
 * return:  0 - swapping done
 *         -1 - no more zeros in this col
 */

int seekAndSwap(double matrix[][4],double vector[],int row,int col,int dim){
    
    int i = row,j;

    while(dim<i && matrix[i][col]==0){
        i++;
    }

    // seems the was no non-zero value in colum <col> below row <row>
    if(i==dim){
        return -1;
    }
    // swap row <row> with row <i>
    
    if(i!=row){
        double tmp;

        // swap row parts begining with col
        for(j=col;j<dim;j++){
            tmp             = matrix[row][j];
            matrix[row][j]  = matrix[i][j];
            matrix[i][j]    = tmp;
        }
        // swap elements in vector
        tmp         = vector[row];
        vector[row] = vector[i];
        vector[i]   = tmp;
    }

    return 0;
}



/*
 * Eliminates colum <col> of row <traget> by subtracting row <source> from
 * row <target>, after multiplying row <target> with the needed factor. 
 * Also Aplly all changes to vector.
 */
void multiplyAndKill(double matrix[][4],double vector[],
                     int source,int target,int col,int dim){
    int i;

    double factor = matrix[source][col]/matrix[target][col];

    printf("Matrix before change (factor will be: %f): \n",factor);
    printSquareMatrixandVector(matrix,vector,dim);

    // multiply
    for(i=col;i<dim;i++){
        matrix[target][i] *=factor;
    }

    vector[target] *= factor;
    
    printf("Matrix after multiply: \n");
    printSquareMatrixandVector(matrix,vector,dim);
    
    // kill
    for(i=col;i<dim;i++){
        matrix[target][i] -= matrix[source][i] ;
    }

    vector[target] -= vector[source];

    printf("Matrix after kill: \n");
    printSquareMatrixandVector(matrix,vector,dim);
}

/* 
 * Transform given Matrix to an Triangular if possible. Applies
 * also changes to the vector.
 *
 * return:  0 - all right
 *         -1 - could not transform (not singular??)
 */
int doTriangle(double matrix[][4],double victor[],int dim){
    
    int i,j;
    
    // eliminate next colum
    for(i=0;i<dim;i++){
        // not singular
        if(matrix[i][i] == 0 && seekAndSwap(matrix,victor,i,i,dim) != 0){
            return(-1);
        }
        
        // substract for other rows
        for(j=i+1;j<dim;j++){
            multiplyAndKill(matrix,victor,i,j,i,dim);
        }
    }

    return 0;
}

void solve(double matrix[][4],double vector[],double sol[],int dim){
    
    int i,j;
    double sum;

    for(i=dim-1;i>=0;i--){
        sum=0;
        for(j=i;j<dim;j++){
            sum += matrix[i][j]; 
        }
        sol[i]=vector[i]/sum;
    }
}


int main(int argc, char** argv)
{
    //double matrix [4][4];
    double b[4]=
        { -7.53,  6.06,  8.05, -8.10};
    double sol[4];
    double matrix[4][4] = {
        {  6.22,  1.42, -1.72,  1.91},
        {  1.44,  5.33,  1.11, -1.82},
        {  1.59, -1.23, -5.24, -1.42},
        {  1.75, -1.69,  1.57,  6.55}
    };

#ifdef TEST
    double test[4][4] = {
        {  6.22,  1.42, -1.72,  1.91},
        {  1.44,  5.33,  1.11, -1.82},
        {  1.59, -1.23, -5.24, -1.42},
        {  1.75, -1.69,  1.57,  6.55}
    };
#endif
    
    int i,j;
    
    if(doTriangle(matrix,b,4)==-1){
        printf("Unable to build tiragular matrix \r\n");
        return EXIT_SUCCESS;
    }
    
    printf("triangular matrix:\r\n");
    for(i=0;i<4;i++){
        printf("|");
        for(j=0;j<4;j++){
            printf(" %lf ",matrix [i][j]);
        }
        printf("|\t| %lf | \r\n",b[i]);
    }

    solve(matrix,b,sol,4);
    
    printf("\r\nSolution:\r\n");

    for(i=0;i<4;i++){
        printf("| %lf | \r\n",sol[i]);
    }

#ifdef TEST
    // testing the solution
/* This should be the correct solution
    sol[0]=-1.259937697;
    sol[1]=-0.7148628406;
    sol[2]=-1.558092707;
    sol[3]=-0.7109956762;
*/
    printf("\r\nTest:\r\n");

    for(i=0;i<4;i++){
        double res=0;
        for(j=0;j<4;j++){
            res += test[i][j]*sol[i];
        }
        printf("| %lf |\r\n",res);
    }
#endif

    return EXIT_SUCCESS;
}
