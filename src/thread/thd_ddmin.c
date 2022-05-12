#include <stdio.h>
#include <stdlib.h>
#include "../../include/runner.h"
#include "../../include/ddmin.h"
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
thd_ddmin (char * executeFile_path, char * inputFile_path, char * ans) {
	
	int file_size;
	int initial_size;
	char * current_file_path = (char *) malloc (100);
	strcpy(current_file_path, "log0");
	
	FILE * temp_file = fopen(current_file_path, "w+") ;
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
	
	// range algorithm
	thd_range(executeFile_path, "temp", ans) ;
	
	return current_file_path;
}
