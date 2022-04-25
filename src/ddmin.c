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

char *
ddmin (char * executeFile_path, char * inputFile_path) {
	
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
		stat("temp", &st);
		file_size = st.st_size;
		if (n > file_size) {
			n = file_size;
		}
        
		result_file_path = reduce_to_substring(executeFile_path, "temp", n);
		if (strcmp(result_file_path, "temp") != 0) {
			fprintf(stderr, "result of substring\n");
			n = 2;
			free(result_file_path);
			continue ;
		}
			
		result_file_path = reduce_to_complement(executeFile_path, "temp", n);
		if (strcmp(result_file_path, "temp") != 0) {
			fprintf(stderr, "result of complement\n");
			n = 2;
			free(result_file_path);
		}
		else {
			n = n * 2;
		}
		fprintf(stderr, "[%d %d]\n", file_size, n) ;
	} 
    	while ((file_size > 1) && (file_size * 2 != n));
	
	return current_file_path;
}