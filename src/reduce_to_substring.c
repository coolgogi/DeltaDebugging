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
reduce_to_substring (char * executeFile_path, char * input_file_path, int n, int * len) {

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

		runner(executeFile_path, substring, "output/ddmin_output.txt");
	        
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
