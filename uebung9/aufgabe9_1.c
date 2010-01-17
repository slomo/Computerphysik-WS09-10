#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 1

double h10(double x) {
    return pow(x,10)-45*pow(x,8)+630*pow(x,6)-3150*pow(x,4)+4725*pow(x,2)-945;
}

double phi10(double x) {
    return A*pow(M_E,(-pow(x,2.0)/2.0))*h10(x);
}

double abs_phi10_pow2(double x) {
    return pow(fabs(phi10(x)),2);
}

double abs_phi10_pow2_d(double x) {
    // y = -2*x*e^(-x^2)*(x^10-45*x^8+630*x^6-3150*x^4+4725*x^2-945)*(x^10-55*x^8+990*x^6-6930*x^4+17325*x^2-10395)
    return -2*x*pow(M_E,-pow(x,2))*(pow(x,10)-45*pow(x,8)+630*pow(x,6)-3150*pow(x,4)+4725*pow(x,2)-945)*(pow(x,10)-55*pow(x,8)+990*pow(x,6)-6930*pow(x,4)+17325*pow(x,2)-10395);
}

// function gets a range from a to b, a function, the derivative of the function, a accuracy and a startvalue
// it retruns the root of the function in the interval
double newton_raphson(double a,double b, double(*f)(double), double(*df)(double), double acc, double start) {
    double value,dx,fx,d;

    value = start;
    fx=f(value);
    dx=df(value);

    while(!(fabs(d) < acc)) {
        d = -fx/dx;
        value += d;

        // when calculation jumps out of range return a value out of range
        if ((a-value)*(value-b) < 0.0) {
            return a-1;
        }

        fx=f(value);
        dx=df(value);
    }
    return value;
}

int main(int argc, char** argv)
{
    
    return EXIT_SUCCESS;
}
