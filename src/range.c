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
range (char * execute_file_path, char * input_file_path, char * ans) {
	
	copy_file(input_file_path, "temp") ;

	struct stat st ;
	stat("temp", &st) ;
	int file_size = st.st_size ;
	
	int cnt = 0 ;
	char output[300] ;
	
	int answer_index = 0 ;
	for (int range_size = file_size - 1 ; range_size > 0 ; range_size --) {
		FILE * read_file_ptr = fopen("temp", "r") ;
		for (int begin = 0 ; begin <= file_size - range_size ; begin ++) {
			int end = begin + range_size ;
			FILE * write_file_ptr = fopen("complement", "w+") ;
			write_file(read_file_ptr, write_file_ptr, 0, begin) ;
			write_file(read_file_ptr, write_file_ptr, end, file_size) ;
			fclose(write_file_ptr) ;	
			remove("stderr") ;
			EXITCODE rt = r_runner(execute_file_path, "complement", "ddmin_stdout") ;
			cnt ++ ;
			FILE * stderr_ptr = fopen("stderr", "r") ;
			if (stderr_ptr == NULL) {
				fclose(stderr_ptr) ;
				continue ;
			}		

			while (!feof(stderr_ptr)) {
				memset(output, 0, 300) ;
				fgets(output, 300, stderr_ptr) ;
				if (strstr(output, ans) != NULL) {
					char new_temp_path[10] ;
					sprintf(new_temp_path, "temp%d", answer_index) ;
					answer_index++ ;
					copy_file("complement", new_temp_path) ;
					break ;
				}
			}
			fclose(stderr_ptr) ;
		}
		fclose(read_file_ptr) ;
                if (answer_index > 0) {
                        srand(time(NULL)) ;
                        int rnum = rand() % answer_index ;
                        char selected_path[10] ;
                        sprintf(selected_path, "temp%d", rnum) ;

                        copy_file(selected_path, "temp") ;

                        answer_index = 0 ;
                        stat("temp", &st) ;
                        file_size = st.st_size ;
                        range_size = MIN(file_size, range_size + 1) ;
                }
	}
	printf("cnt: %d\n",cnt) ;
}

