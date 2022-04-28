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
reduce_to_substring (char * executeFile_path, char * input_file_path, int n, int * len, double p2) {

	struct stat st;
	stat(input_file_path, &st);
	char * substring = (char *) malloc (21);

	char ans[3][15] ;
        memset(ans[0], 0, 15) ;
        memset(ans[1], 0, 15) ;
        memset(ans[2], 0, 15) ;
        strcpy(ans[0], "jsondump.c:33") ;
        strcpy(ans[1], "jsondump.c:44") ;
        strcpy(ans[2], "jsondump.c:120") ;
	
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
		if (rt.code_num != 1) {
			remove("stderr") ;
			continue ;
		}		

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
                if (strstr(std[0], "33") != NULL && strstr(std[1], "44") != NULL && strstr(std[2], "120") != NULL) {
			// store
			
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
			
			//
			/*		
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
			*/	
		}
		
	}
	// random select
	
	if (file_index != 0) {
		fprintf(stderr, "substring: %d\n", file_index) ;
		srand(time(NULL)) ;
		int rand_num = rand() % file_index ;
		sprintf(substring, "substring%d", rand_num) ;
		// change temp
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

	//
	free(substring);
	return input_file_path;
}
