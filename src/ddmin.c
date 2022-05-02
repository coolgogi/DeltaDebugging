#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/param.h>

char *
ddmin (char * executeFile_path, char * inputFile_path, double p, double p2, double sigma, char * ans) {
	
	int n = 2 ;
	int file_size;
	char * current_file_path = (char *) malloc (100);
	strcpy(current_file_path, "temp");
	
	FILE * temp_file = fopen("temp", "w+") ;
	FILE * input_file = fopen(inputFile_path, "r") ;
	unsigned char buf ; 
	while (fread(&buf, 1, 1, input_file)) {
		fwrite(&buf, 1, 1, temp_file) ;
	}
	fclose(input_file) ;
	fclose(temp_file) ;

     	char * result_file_path ;
	struct stat st;

	do {
		double rand_num ;
		struct timeval tv ;

		stat("temp", &st);
		file_size = st.st_size;
		if (n > file_size) {
			n = file_size;
		}
       		int * len = split(file_size, n, sigma) ; 
		
		
		gettimeofday(&tv, NULL) ;	
		srand(tv.tv_usec) ;
		rand_num = (double) rand() / (double) RAND_MAX;
		if (p >= rand_num) {
			result_file_path = reduce_to_substring(executeFile_path, "temp", n, len, p2, ans);
			if (strcmp(result_file_path, "temp") != 0) {
				n = 2;
				free(result_file_path);
				continue ;
			}
		}
		
		gettimeofday(&tv, NULL)	;
		srand(tv.tv_usec) ;
		rand_num = (double) rand() / (double) RAND_MAX;
		if (p >= rand_num) {
			result_file_path = reduce_to_complement(executeFile_path, "temp", n, len, p2, ans);
			if (strcmp(result_file_path, "temp") != 0) {
				n = MAX(n-1, 2) ;
				free(result_file_path);
			}
			else {
				n = n * 2;
			}
		}
		free(len) ;
	} 
    	while ((file_size > 1) && (file_size * 2 != n));
	
	return current_file_path;
}
