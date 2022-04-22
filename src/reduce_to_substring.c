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

char *
reduce_to_substring (char * executeFile_path, char * input_file_path, int n) {

	struct stat st;
	stat(input_file_path, &st);
	int size = (int) ceil((double)st.st_size / n);

	char * substring = (char *) malloc (21);

	for (int i = 0 ; i < n ; i ++ ) {
		sprintf(substring, "substring");
		FILE * read_file = fopen(input_file_path, "r") ;
		remove(substring) ;
		FILE * write_file = fopen(substring, "w+");
		fseek(read_file, i*size, SEEK_SET) ; 
		for (int j = 0 ; j < size ; j ++) {
			unsigned char buf ;
			if (fread(&buf, 1, 1, read_file) != 1) {
				break;
			}
			fwrite(&buf, 1, 1, write_file);

		}
		fclose(write_file) ;
		fclose(read_file) ;

		EXITCODE rt = runner(executeFile_path, substring, "output/ddmin_output.txt");
		if (rt.code_num == 1) {
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
