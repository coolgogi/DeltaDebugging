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
r_ddmin (char * executeFile_path, char * inputFile_path, char * ans, double p) {
	
	int n = 2 ;
	int file_size;
	int initial_size;
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
	stat("temp", &st);
	initial_size = st.st_size ;

	do {

		stat("temp", &st);
		file_size = st.st_size;
		double prop = (double) file_size / (double) initial_size ;

		if (n > file_size) {
			n = file_size;
		}
		
		if (prop <= p) {
			// range algorithm
			range(executeFile_path, "temp", ans) ;
			break ;
		}

      	 	int * len ;
		len = o_split(file_size, n) ; 
			
		result_file_path = r_substring(executeFile_path, "temp", n, len, ans);
		if (strcmp(result_file_path, "temp") != 0) {
			n = 2;
			free(result_file_path);
			continue ;
		}
		
		result_file_path = r_complement(executeFile_path, "temp", n, len, ans);
		if (strcmp(result_file_path, "temp") != 0) {
			n = MAX(n - 1, 2) ;
			free(result_file_path);
		}
		else {
			n = n * 2;
		}
		free(len) ;
	
	
	} 
    	while ((file_size > 1) && (file_size * 2 != n));
	
	return current_file_path;
}
