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

void
writeFile (FILE * read_file, FILE * write_file, int len, unsigned char * buf) {
        int buf_size = sizeof(&buf) / sizeof(unsigned char) ;
        int loop = len / buf_size ;
        int mod = len % buf_size ;
        for (int i = 0 ; i < loop ; i ++) {
                if (fread(buf, buf_size, 1, read_file) == 1) {
                        fwrite(buf, buf_size, 1, write_file) ;
                }
        }
        if (fread(buf, mod, 1, read_file) == 1) {
                fwrite(buf, mod, 1, write_file) ;
        }
}


char *
r_ddmin (char * executeFile_path, char * inputFile_path, char * ans, double p) {
	
	struct stat st ;
	stat(inputFile_path, &st) ;
	int file_size = st.st_size ;
	char * current_file_path = (char *) malloc(5);
	strcpy(current_file_path, "temp");
	
	FILE * temp_file = fopen(current_file_path, "w+") ;
	FILE * input_file = fopen(inputFile_path, "r") ;
	unsigned char * buf = (unsigned char *) malloc(1024) ;
	memset(buf, 0, 1024) ;
	writeFile(input_file, temp_file, file_size, buf) ;
	free(buf) ;
	fclose(input_file) ;
	fclose(temp_file) ;

	range(executeFile_path, current_file_path, ans) ;
	
	return current_file_path;
}
