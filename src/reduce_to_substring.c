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
reduce_to_substring (char * executeFile_path, char * input_file_path, int n, int * len, double p2, char * ans) {

	struct stat st;
	stat(input_file_path, &st);
	char * substring = (char *) malloc (21);
	
	int file_index = 0 ;

	int begin = 0 ;
	for (int i = 0 ; i < n ; i ++ ) {
		sprintf(substring, "substring");
		FILE * read_file = fopen(input_file_path, "r") ;
		remove(substring) ;
		FILE * write_file = fopen(substring, "w+");
		fseek(read_file, begin, SEEK_SET) ; 
		for (int j = 0 ; j < len[i] ; j ++) {
			unsigned char buf ;
			if (fread(&buf, 1, 1, read_file) != 1) {
				break;
			}
			fwrite(&buf, 1, 1, write_file);
		}
		begin = begin + len[i] ;
		fclose(write_file) ;
		fclose(read_file) ;

		EXITCODE rt = runner(executeFile_path, substring, "output/ddmin_output.txt");
		if (rt.code_num != 77) {
			remove("stderr") ;
			continue ;
		}		

		FILE * stderr_ptr = fopen("stderr", "r") ;
                char std[3][300] ;
                memset(std[0], 0, 300) ;
		
		while (!feof(stderr_ptr)) {
			fgets(std[0], 300, stderr_ptr) ;
			if (strstr(std[0], ans) != NULL) {
				break ;
			}
		}
		fclose(stderr_ptr) ;
                remove("stderr") ;

		if (strstr(std[0], ans) != NULL) {
			char save_substring[20] ;
			memset(save_substring, 0, 20) ;
			sprintf(save_substring, "substring%d", file_index) ;
			file_index ++ ;
			
			if (access(save_substring, F_OK) == 0) {
				remove(save_substring) ;
			}
			FILE * file_candidate = fopen(save_substring, "w+") ;
			FILE * result_file = fopen(substring, "r") ;
			unsigned char buf ;
			while (fread(&buf, 1, 1, result_file)) {
				fwrite(&buf, 1, 1, file_candidate) ;
			}
			fclose(result_file) ;
			fclose(file_candidate) ;
			
		}
		
	}
	
	if (file_index != 0) {
		srand(time(NULL)) ;
		int rand_num = rand() % file_index ;
		sprintf(substring, "substring%d", rand_num) ;
		remove("temp") ;
		FILE * new_temp = fopen("temp", "w+") ;
		FILE * result_file = fopen(substring, "r") ;
		unsigned char buf ;
		
		while (fread(&buf, 1, 1, result_file)) {
			fwrite(&buf, 1, 1, new_temp);
		}
		fclose(result_file);
		fclose(new_temp);
		
		return substring ;	
	}
	
	free(substring);
	return input_file_path;
}
