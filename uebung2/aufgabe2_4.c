#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef GMP

#include <gmp.h>

#endif

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

double fak_stirling(double x)
{
    return exp(x*log(x)-x);
}

#ifdef GMP

//Function to calculate fak with nearly unlimited size using gmp algebra lib
//gmp have to be installed otherwise the last operation of the makefile will fail
//2 binaries will be generated one with gmp support and one without
void fak_gmp(mpz_t *x)
{
	mpz_t i;
	mpz_t returnvalue;
	
	mpz_init_set_ui(returnvalue, 1);
	
	for(mpz_init_set_ui(i,1); mpz_cmp(i,*x)<=0; mpz_add_ui(i,i,1)) {
		mpz_mul(returnvalue,returnvalue,i);
	}
	mpz_set(*x,returnvalue);

	//cleanup
	mpz_clear(i);
	mpz_clear(returnvalue);
}
#endif

int main(int argc, char* argv[])
{
    if(argc==2) {
        int n;
        //When -p is given as a parameter, print plotable values for n=(10,20,...,100)
        if (!strcmp(argv[1],"-p")) {
            for (n=10;n<=100;n+=10){
                printf("%d %.0f %.0f\n",n,fak_double(n),fak_stirling(n));
            }
        }
        else {
            n = atoi(argv[1]); //get value from agrument
        
            printf("Fak(%d) useing Integer : %d\n",n,fak_int(n));
            printf("Fak(%d) useing Float   : %.0f\n",n,fak_float(n));
            printf("Fak(%d) useing Double  : %.0f\n",n,fak_double(n)); 
            printf("Fak(%d) useing Stirling: %.0f\n",n,fak_stirling(n));

            #ifdef GMP
    	    mpz_t num;
    	    mpz_init_set_str (num, argv[1], 10);
    		fak_gmp(&num);
    		printf("Fak(%d) useing GMP     : ",n);
    		mpz_out_str(NULL,10,num);
    		printf("\n");
    	    mpz_clear(num);
            #endif
        }
    }
    else {

        printf("Max Values:\n");
        printf("Fak(12) useing Integer: %d\n",fak_int(12));          //max=12
        printf("Fak(13) useing Integer: %d\n  -> overflow should be %.0f\n\n",fak_int(13),fak_float(13));      //overflow
    
        printf("Fak(34) useing Float  : %.0f\n",fak_float(34));      //max=34
        printf("Fak(35) useing Float  : %.0f\n\n",fak_float(35));    //equals inf

        printf("Fak(170) useing Double : %.0f\n",fak_double(170));   //max=170  
        printf("Fak(171) useing Double : %.0f\n\n",fak_double(171)); //equals inf
   }
   return EXIT_SUCCESS;
}
