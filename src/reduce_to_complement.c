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

char *
reduce_to_complement(char * executeFile_path, char * input_file_path, int n) {

	struct stat st;
	stat(input_file_path, &st);
	int size = (int) ceil((double)st.st_size / n);
	char * complement = (char *) malloc (21);

	for (int i = 0 ; i < n ; i ++) {
		int total = 0 ;
		sprintf(complement, "complement");
		FILE * read_file = fopen(input_file_path, "r");
		remove(complement) ;
		FILE * write_file = fopen(complement, "w+");
		for (int j = 0 ; j < n ; j ++) {
			for (int k = 0 ; k < size ; k ++) {
				unsigned char buf ;
				if(fread(&buf, 1, 1, read_file) != 1) {
					break ;
				}
				if (i == j) {
					continue ;
				}
				fwrite(&buf, 1, 1, write_file);
				total ++ ;
			}
		}
		fclose(write_file);
		fclose(read_file) ;
		
		if (total == st.st_size)
			continue ;

		EXITCODE rt = runner(executeFile_path, complement, "output/ddmin_output.txt");
		if (rt.code_num == 1) {
			remove("temp") ;
			FILE * new_temp = fopen("temp", "w+") ;
			FILE * result_file = fopen(complement, "r") ;
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
