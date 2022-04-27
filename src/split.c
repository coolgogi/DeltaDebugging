#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <math.h>

int *
split (int file_size, int n, double sigma) {
	
	double mean = ceil(((double) file_size - (double) n) / (double) n) ;
	const gsl_rng_type * T ;
	gsl_rng * r ;
	gsl_rng_env_setup() ;
	T = gsl_rng_default ;
	r = gsl_rng_alloc(T) ;
	gsl_rng_set(r, (int) time(NULL)) ;

	int * len = calloc(sizeof(int), n) ;
	memset(len, 0, sizeof(int) * n) ;
	
	int sum_allots = 0 ;
	for (int i = 0 ; i < n - 1 ; i ++) {
		int allot ;
		allot = round(gsl_ran_gaussian(r, sigma) + mean) ;

		if (allot < 0 ) {
			allot = 0 ;
		}
		else {
			if (allot + sum_allots > file_size - n) {
				if (sum_allots == file_size - n) {
					allot = 0 ;
				}
				else {
					allot = file_size - n - sum_allots ; 
				}
			}
		}
		len[i] = 1 + allot ;
		sum_allots = sum_allots + allot ;
	}
	len[n - 1] = (file_size - n) - sum_allots + 1 ;
		
	gsl_rng_free(r) ;
	
	return len ;
}
