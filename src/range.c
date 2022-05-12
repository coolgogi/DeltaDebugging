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
range (char * executeFile_path, char * input_file_path, char * ans) {
	
	struct stat st ;
	stat(input_file_path, &st) ;
	char * complement ;
	complement = (char *) malloc (30) ;
	sprintf(complement, "complement") ;
	int file_size = st.st_size ;
	
	int cnt = 0 ;
	int begin = 0 ;
	for (int range_size = file_size - 1 ; range_size > 0 ; range_size --) {
		for ( ; begin <= file_size - range_size ; begin ++) {
			int end = begin + range_size ;
			FILE * read_file = fopen(input_file_path, "r") ;
			FILE * write_file = fopen(complement, "w+") ;

			if (begin != 0) {
				int num = begin ;
				unsigned char * buf = (unsigned char *) malloc (num) ;
				fread(buf, num, 1, read_file) ;
				fwrite(buf, num, 1, write_file) ;
				free(buf) ;
			}
			fseek(read_file, end, SEEK_SET) ;
			if (end != file_size) {
				int num = file_size - end ;	
				unsigned char * buf = (unsigned char *) malloc (num) ;
				fread(buf, num, 1, read_file) ;
				fwrite(buf, num, 1, write_file) ;
				free(buf) ;
			}

			fclose(write_file) ;
			fclose(read_file) ;
			
			EXITCODE rt = r_runner(executeFile_path, complement, "ddmin_stdout") ;
			cnt ++ ;
			FILE * stderr_ptr = fopen("stderr", "r") ;
			if (stderr_ptr == NULL) {
				continue ;
			}	
			char output[300] ;
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
				remove("temp") ;
				FILE * new_temp = fopen("temp", "w+") ;
				FILE * result_file = fopen(complement, "r") ;
				unsigned char buf ;
				while (fread(&buf, 1, 1, result_file)) {
					fwrite(&buf, 1, 1, new_temp) ;
				}
				fclose(result_file) ;
				fclose(new_temp) ;
				stat("temp", &st) ;
				file_size = st.st_size ;
				range_size = MIN(range_size + 1, file_size) ;
				begin = MAX(0, begin - range_size + 1)  ;
				break ;
			}
		}
		if (begin > file_size - range_size) {
			begin = 0 ;
		}
		
	}
	free(complement) ;
	printf("cnt: %d\n",cnt) ;

}

