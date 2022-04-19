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
//		sprintf(complement, "output/ddmin-%d", i);		
		sprintf(complement, "complement");

		FILE * read_file = fopen(input_file_path, "r");
		FILE * write_file = fopen("complement", "w+a");
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
			}
		}
		fclose(write_file);
		fclose(read_file) ;

		EXITCODE rt = runner(executeFile_path, "complement", "output/ddmin_output.txt");
		if (rt.code_num == 1) {
			FILE * answer_file = fopen("output/dd_answer", "w+");
			FILE * failing_file = fopen("complement", "r");
			unsigned char buf;
			while (fread(&buf, 1, 1, failing_file)) {
				fwrite(&buf, 1, 1, answer_file);
			}
			fclose(failing_file);
			fclose(answer_file);
			return complement;

		}
	}

	free(complement);
	return input_file_path;
}
