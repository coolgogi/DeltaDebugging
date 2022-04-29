#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

char *
o_substring (char * executeFile_path, char * input_file_path, int n, int * len, char * ans) {

	struct stat st;
	stat(input_file_path, &st);
	char * substring = (char *) malloc (21);
	
	int sum = 0 ;	
	for (int i = 0 ; i < n ; i ++ ) {
		sprintf(substring, "substring");
		remove(substring) ;
		FILE * write_file = fopen(substring, "w+");
		FILE * read_file = fopen(input_file_path, "r") ;
		fseek(read_file, sum, SEEK_SET) ; 
		for (int j = 0 ; j < len[i] ; j ++) {
			unsigned char buf ;
			if (fread(&buf, 1, 1, read_file) != 1) {
				break;
			}
			fwrite(&buf, 1, 1, write_file);
		}
		sum = sum + len[i] ; 

		fclose(write_file) ;
		fclose(read_file) ;

		EXITCODE rt = o_runner(executeFile_path, substring, "output/ddmin_output.txt");
		FILE * stderr_ptr = fopen("stderr", "r") ;
                char output[300] ;
                memset(output, 0, 300) ;
		
		while (!feof(stderr_ptr)) {
			fgets(output, 300, stderr_ptr) ;
			if (strstr(output, ans) != NULL) {
				break ;
			}
		}
		fclose(stderr_ptr) ;
                remove("stderr") ;

		if (strstr(output, ans) != NULL) {
			remove("temp") ;
			FILE * new_temp = fopen("temp", "w+") ;
			FILE * result_file = fopen(substring, "r") ;
			unsigned char buf ;
			while (fread(&buf, 1, 1, result_file)) {
				fwrite(&buf, 1, 1, new_temp);
			}
			fclose(result_file);
			fclose(new_temp);
			return substring;
		}
		
	}
	free(substring);
	return input_file_path;
}
