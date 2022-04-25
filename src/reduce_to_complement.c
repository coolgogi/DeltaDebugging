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
	
	char ans[3][30] ;
    memset(ans[0], 0, 30) ;
    memset(ans[1], 0, 30) ;
    memset(ans[2], 0, 30) ;
	strcpy(ans[0], "in dump jsondump.c:33\n") ;
	strcpy(ans[1], "in dump jsondump.c:44\n") ;
	strcpy(ans[2], "in main jsondump.c:120\n") ;

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

		FILE * stderr_ptr = fopen("stderr", "r") ;
        char std[3][100] ;
        memset(std[0], 0, 100) ;
        memset(std[1], 0, 100) ;
        memset(std[2], 0, 100) ;
        fgets(std[0], 100, stderr_ptr) ;
        fgets(std[0], 100, stderr_ptr) ;
        fgets(std[0], 100, stderr_ptr) ;
        fgets(std[0], 100, stderr_ptr) ;
        fgets(std[0], 100, stderr_ptr) ;
        fgets(std[1], 100, stderr_ptr) ;
        fgets(std[2], 100, stderr_ptr) ;
		fclose(stderr_ptr) ;
		printf("%s\n%s\n%s\n", std[0]+19, std[1]+19, std[2]+19) ;
        if (strncmp(ans[0], std[0]+19, 21) == 0 && strncmp(ans[1], std[1]+19, 21) == 0 && strncmp(ans[2], std[2]+19, 22) == 0) {
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
