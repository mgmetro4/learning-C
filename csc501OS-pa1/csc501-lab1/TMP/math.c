/* math.c */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include "math.h"
#include "sched.h"

/*
 *  generates random numbers that follow exponential distribution
 *  return double
 */
double expdev(double lambda) {

	double dummy;
	do
		dummy = (double) rand() / RAND_MAX;
		while (dummy == 0.0);
	
	return -log(dummy)/lambda;
}

/*
 * caluclate exponential value of x to the p power
 * return double
 */
double pow(double x, int p) {
	if(p == 0) {
		return x;
	}
	
	int i;
	double val;
	
	if(p > 0) {
		val = x;
		for(i=1; i<p; i++) {
			val = val*x;
		}
	}
	
	if(p < 0) {
		val = 1;
		for(i=1; i < p; i++) {
			val = val/x;
		}
	}
	
	return val;
}

/*
 *  calculate natural log of a float between [0,2] only using Taylor's Expansion
 *  return double
 */
double log(double x) {
	int n = 20;
	double nlog = 0.0;
	int i;

	for(i=1; i<=n; i=i+2) {
		nlog = nlog + (pow(((x-1)/(x+1)),i)/i);
	}	
	
	return nlog*2;
}






