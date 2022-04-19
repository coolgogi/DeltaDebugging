#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include "../include/runner.h"
#include "../include/ddmin.h"


char *
reduce (char * executeFile_path, char * input_file_path, int n) {

	struct stat st ;
	stat(input_file_path, &st) ;
	int size = (int) ceil((double)st.st_size / n) ;
	
	char substring[10] = "substring" ;
	char complement[11] = "complement" ;
	char * rt_path = (char *) malloc (12) ;
	FILE * read_file = fopen(input_file_path, "r") ;
	if (read_file == NULL) {
		perror("reduce.c: ") ;
		exit(EXIT_FAILURE) ;
	}
	
	for (int i = 0 ; i < n ; i ++) {
		FILE * substring_file = fopen(substring, "w+") ;
		FILE * complement_file = fopen(complement, "w+") ;
		for (int j = 0 ; j < n  ; j ++) {
			for (int k = 0 ; k < size ; k ++) {
				unsigned char buf ;
				if(fread(&buf, 1, 1, read_file) != 1) {
					break ;
				}
				if (i == j) {
					fwrite(&buf, 1, 1, substring_file) ;	
				}
				else {
					fwrite(&buf, 1, 1, complement_file) ;
				}
			}	
		}
		fclose(complement_file) ;
		fclose(substring_file) ;

		EXITCODE rt = runner(executeFile_path, substring, "dd_out") ;
		if (rt.code_num == 1) {
			free(complement) ;
			FILE * answer_file = fopen("output/dd_answer", "w+") ;
			FILE * failing_file = fopen(substring, "r") ;
			unsigned buf ;
			while (fread(&buf, 1, 1, failing_file)) {
				fwrite(&buf, 1, 1, answer_file) ;
			}
			fclose(failing_file) ;
			fclose(answer_file) ;
			strcpy(rt_path, substring) ;
			return rt_path ;
		
		}
		rt = runner(executeFile_path, complement, "dd_out") ;
		if (rt.code_num == 1) {
			free(substring) ;
			FILE * answer_file = fopen("output/dd_answer", "w+") ;
			FILE * failing_file = fopen(complement, "r") ;
			unsigned buf ;
			while (fread(&buf, 1, 1, failing_file)) {
				fwrite(&buf, 1, 1, answer_file) ;
			}
			fclose(failing_file) ;
			fclose(answer_file) ;
			strcpy(rt_path, complement) ;
			return rt_path ;	
		}
	}
	free(substring) ;
	free(complement) ;
	
	return input_file_path ;
}

