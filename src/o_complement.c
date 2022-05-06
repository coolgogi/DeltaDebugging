#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <time.h>

char *
o_complement(char * executeFile_path, char * input_file_path, int n, int * len, char * ans) {

	struct stat st;
	stat(input_file_path, &st);
	char * complement = (char *) malloc (21);
	

	for (int i = 0 ; i < n ; i ++) {
		sprintf(complement, "complement");
		remove(complement) ;
		FILE * write_file = fopen(complement, "wb+");
		FILE * read_file = fopen(input_file_path, "rb");
		for (int j = 0 ; j < n ; j ++) {
			for (int k = 0 ; k < len[j] ; k ++) {
				unsigned char buf ;
				if(fread(&buf, 1, 1, read_file) != 1) {
					break ;
				}
				if (i == j) {
					continue ;
				}
				fwrite(&buf, 1, 1, write_file);
			}
		}
		fclose(write_file);
		fclose(read_file) ;
		

		EXITCODE rt = o_runner(executeFile_path, complement, "output/ddmin_output.txt");
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
			FILE * new_temp = fopen("temp", "wb+") ;
			FILE * result_file = fopen(complement, "rb") ;
			unsigned char buf ;
			while (fread(&buf, 1, 1, result_file) == 1) {
				fwrite(&buf, 1, 1, new_temp) ;
			}
			fclose(result_file) ;
			fclose(new_temp) ;
			return complement;

		}
	}
	free(complement);
	return input_file_path;
}
