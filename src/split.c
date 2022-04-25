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

char **
split (char * input_file_path, int n) {
	gsl_rng * temp ;
	gsl_ran_gaussian(temp, 0) ;
}
