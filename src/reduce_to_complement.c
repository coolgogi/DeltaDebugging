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
	
	char ans[3][15] ;
	memset(ans[0], 0, 15) ;
    	memset(ans[1], 0, 15) ;
    	memset(ans[2], 0, 15) ;
	strcpy(ans[0], "jsondump.c:33") ;
	strcpy(ans[1], "jsondump.c:44") ;
	strcpy(ans[2], "jsondump.c:120") ;

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

		//EXITCODE rt = 
		runner(executeFile_path, complement, "output/ddmin_output.txt");

		FILE * stderr_ptr = fopen("stderr", "r") ;
		char temp[200] ;
	        char std[3][60] ;
	        memset(std[0], 0, 60) ;
	        memset(std[1], 0, 60) ;
       		memset(std[2], 0, 60) ;
	        fgets(temp, 200, stderr_ptr) ;
	        fgets(temp, 200, stderr_ptr) ;
	        fgets(temp, 200, stderr_ptr) ;
	        fgets(std[0], 60, stderr_ptr) ;
	        fgets(std[1], 60, stderr_ptr) ;
	        fgets(std[2], 60, stderr_ptr) ;
		fclose(stderr_ptr) ;
		remove("stderr") ;
	       	printf("%s, %s, %s\n" , std[0], std[1], std[2]) ; 
		if (strstr(std[0], "33") != NULL && strstr(std[1], "44") != NULL && strstr(std[2], "120") != NULL) {	
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
