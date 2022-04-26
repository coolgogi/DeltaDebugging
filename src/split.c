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

int *
split (int file_size, int n, double stddev) {
	
	double mean = (double) file_size / (double) n ;
	fprintf(stderr, "mean: %lf\n", mean) ;
	const gsl_rng_type * T ;
	gsl_rng * r ;
	gsl_rng_env_setup() ;
	T = gsl_rng_default ;
	r = gsl_rng_alloc(T) ;
	gsl_rng_set(r, (int) time(NULL)) ;

	double dist[n] ;
	int * len = (int *) malloc (sizeof(int) * n) ;
	memset(len, 0, sizeof(int) * n) ;
	double prop = 0.0 ;
	double total = 0.0 ;
	int maxBound = file_size - n ;
	
	for (int i = 0 ; i < n ; i ++) {
		dist[i] = gsl_ran_gaussian(r, stddev) + mean ;
		fprintf(stderr, "dist[%d]: %lf\n", i, dist[i]) ;
		if (dist[i] <= 1) {
			dist[i] = 1.0 ;
			len[i] = 1 ;
//			maxBound = maxBound - 1 ;
		}
		total = total + dist[i] ;
	}
	fprintf(stderr, "\n") ;
	
	int checker = 0 ;
	for (int i = 0 ; i < n ; i ++) {
		if (i == n-1) {
			len[i] = file_size - checker ;	
			continue ;
		}

		if (len[i] == 0) {
			prop = dist[i] / total ;
			int prop_len = (int) floor (maxBound * prop) ;
			if (prop_len + 1 > 1) {
				len[i] = prop_len + 1;
			}
			else {
				len[i] = 1 ;
			}
		}
		checker = checker + len[i] ;
	}
	gsl_rng_free(r) ;
	
	return len ;	
}
