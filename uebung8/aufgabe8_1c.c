#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rng.h"

void bubbleSort(double numbers[], int array_size)
{
  int i, j, temp;

  for (i = (array_size - 1); i > 0; i--)
  {
    for (j = 1; j <= i; j++)
    {
      if (numbers[j-1] > numbers[j])
      {
        temp = numbers[j-1];
        numbers[j-1] = numbers[j];
        numbers[j] = temp;
      }
    }
  }
}

// This function does the monte carlo integration
// It expects a function, a random number gennerator, the number of
// sampels and and the limits as arguments
// It returns a double with the result of the integration
double casino_royal(double(*f)(double), double(*rng)(long*), int n, double a, double b) {
    int i;
    double *random_numbers,oldValue,currentValue,result;
    double seed;
    
    seed = (long)time(NULL);
    
    random_numbers = malloc(sizeof(double)*n);
    
    // Generate n random Numbers in the given interval
    for(i=0;i<N;i++) {
        random_numbers[i] = a+(rng(&seed)*(b-a));
    }
    bubbleSort(random_numbers,n);
    
    oldValue = f(random_numbers[0]);
    
    for(i=1;i<N;i++) {
        currentValue = f(random_numbers[i]);
        result += (currentValue+oldValue)/2.0 * fabs(currentValue-oldValue);
        oldValue = currentValue;
    }
    return result;
}

int main(int argc, char** argv)
{
    
    return EXIT_SUCCESS;
}
