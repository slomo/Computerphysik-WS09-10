#include<stdlib.h>
#include<stdio.h>
#include<math.h>

double p(double x,double m){
    return(pow(x,m));
}

int main (int argc,char *argv[]){
    int i,m;
    double eArea,nArea,relErr;

    FILE *fErr,*fNum,*fExa;

    //taken from given website
    double x[5] = {   
            0.148875338981163
        ,   0.433395394129247
        ,   0.679409568299024
        ,   0.865063366688985
        ,   0.981560643246719
        };
    double w[5] = {   
            0.295524224714753
        ,   0.269266719309996
        ,   0.219086362515982
        ,   0.149451349159581
        ,   0.066671344308688
        };
    
    fErr = fopen("aufgabe7_2.err","w");
    fNum = fopen("aufgabe7_2.num","w");
    fExa = fopen("aufgabe7_2.exa","w");

    printf("m\tnumeric\t\texakt\t\trelErr\r\n");
    for(m=0;m<=22;m+=2){
        nArea=0;
        for(i=0;i<5;i++){
            nArea+=p(x[i],m)*w[i];
        }
        
        eArea = (1.0/(m+1.0));
        relErr= (nArea/eArea-1)*100;
        
        printf("%d\t%f\t%f\t%f\r\n",m,nArea,eArea,log(fabs(relErr)));

        fprintf(fNum,"%d %f\n",m,nArea);
        fprintf(fExa,"%d %f\n",m,eArea);
        fprintf(fErr,"%d %f\n",m,log(fabs(relErr)));
    }
    fclose(fErr);
    fclose(fNum);
    fclose(fExa);
    return EXIT_SUCCESS;
}
