#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <sys/stat.h>
#include <time.h>
#include <sys/param.h>

void
writeFile (FILE * read_file, FILE * write_file, int len, unsigned char * buf) {
        int buf_size = sizeof(&buf) / sizeof(unsigned char) ;
        int loop = len / buf_size ;
        int mod = len % buf_size ;
        for (int i = 0 ; i < loop ; i ++) {
                if (fread(buf, buf_size, 1, read_file) == 1) {
                        fwrite(buf, buf_size, 1, write_file) ;
                }
        }
        if (fread(buf, mod, 1, read_file) == 1) {
                fwrite(buf, mod, 1, write_file) ;
        }
}

void
range (char * executeFile_path, char * input_file_path, char * ans) {

	struct stat st ;
        stat(input_file_path, &st) ;
        int file_size = st.st_size ;
        char * current_file_path = (char *) malloc(5);
        strcpy(current_file_path, "temp");

        FILE * temp_file = fopen(current_file_path, "w+") ;
        FILE * input_file = fopen(input_file_path, "r") ;
        unsigned char * buf = (unsigned char *) malloc(1024) ;
        memset(buf, 0, 1024) ;
        writeFile(input_file, temp_file, file_size, buf) ;
        fclose(input_file) ;
        fclose(temp_file) ;

	char * complement = (char *) malloc(12) ;
	sprintf(complement, "complement") ;
	int cnt = 0 ;
	int begin = 0 ;
	FILE * read_file = fopen(current_file_path, "r") ;
	char output[300] ;
	for (int range_size = file_size - 1 ; range_size > 0 ; range_size --) {
		for ( ; begin <= file_size - range_size ; begin ++) {
			int end = begin + range_size ;
			FILE * write_file = fopen(complement, "w+") ;
			fseek(read_file, 0, SEEK_SET) ;
			if (begin != 0) {
				writeFile(read_file, write_file, begin, buf) ;
			}
			fseek(read_file, end, SEEK_SET) ;
			if (end != file_size) {
				writeFile(read_file, write_file, file_size - end, buf) ;
			}
			fclose(write_file) ;
			
			EXITCODE rt = r_runner(executeFile_path, complement, "ddmin_stdout") ;
			cnt ++ ;
			FILE * stderr_ptr = fopen("stderr", "r") ;
			if (stderr_ptr == NULL) {
				continue ;
			}		

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
				remove(current_file_path) ;
				FILE * new_temp = fopen(current_file_path, "w+") ;
				FILE * result_file = fopen(complement, "r") ;
				stat(complement, &st) ;
				file_size = st.st_size ;
				writeFile(result_file, new_temp, file_size, buf) ;
				fclose(result_file) ;
				fclose(new_temp) ;
				range_size = MIN(range_size + 1, file_size) ;
				begin = MAX(0, begin - range_size + 1)  ;
				
				fclose(read_file) ;
				read_file = fopen(current_file_path, "r") ;
				break ;
			}
		}
		if (begin > file_size - range_size) {
			begin = 0 ;
		}
		
	}
	free(buf) ;
	free(complement) ;
	free(current_file_path) ;
	printf("cnt: %d\n",cnt) ;
}

