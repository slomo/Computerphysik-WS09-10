/*
*
*   rng.h
*
*   double ran(long *) - Expects pointer to a long-type variable and returns a pseudo random number of uniform distribution in [0,1].
*
*   NOTICE: Initialize the generator by assigning a seed by calling the time function or providing a chosen value before you call it the first time!
*
*   EXAMPLE:
*   long seed = (long) time();
*   double RandomNumber = ran(&seed);
*
*/

#ifndef CP_RNG
#define CP_RNG

/* needs math library */
#include <math.h>

/* some constants for the generator */
#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

/* call this function in your main code and always provide the address of your seed */
double ran(long *);

#endif
