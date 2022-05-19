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

int
find_answer_string (char * stderr_path, char * ans) {
	char buffer[1025];
	memset(buffer, 0, 1025);
	FILE * stderr_file_ptr = fopen(stderr_path, "r");
	struct stat st;
	stat(stderr_path, &st);

	int div = st.st_size / 1024;
	int mod = st.st_size % 1024;
	for (int i = 0; i < div; i++) {
		if (fread(buffer, 1024, 1, stderr_file_ptr) == 1) {
			if (strstr(buffer, ans) != NULL) {
				fclose(stderr_file_ptr);
				return 1;
			}
		}
	}
	if (fread(buffer, mod, 1, stderr_file_ptr) == 1) {
		if (strstr(buffer, ans) != NULL) {
			fclose(stderr_file_ptr);
			return 1;
		}
	}
	for (int i = 0; i < div; i++) {
		int offset = 1024 * (i + 1);
		fseek(stderr_file_ptr, offset - strlen(ans), SEEK_SET);
		int len = MIN(strlen(ans) * 2, strlen(ans) + mod);
		if (fread(buffer, len, 1, stderr_file_ptr) == 1) {
			if (strstr(buffer, ans) != NULL) {
				fclose(stderr_file_ptr);
				return 1;
			}
		}
	}
	fclose(stderr_file_ptr);
	return 0;
}

void
range (char * execute_file_path, char * input_file_path, char * ans) {
	
	int cnt = 0;

	copy_file(input_file_path, "temp");

	struct stat st;
	stat("temp", &st);
	int file_size = st.st_size;
	char output[300];
	int answer_index = 0;
	for (int range_size = file_size - 1; range_size > 0; range_size--) {
		FILE * read_file_ptr = fopen("temp", "r");
		for (int begin = 0; begin <= file_size - range_size; begin++) {
			int end = begin + range_size;
			
			FILE * write_file_ptr = fopen("complement", "w+");
			write_file(read_file_ptr, write_file_ptr, 0, begin);
			write_file(read_file_ptr, write_file_ptr, end, file_size);
			fclose(write_file_ptr);	

			remove("stderr");
			EXITCODE rt = r_runner(execute_file_path, "complement", "ddmin_stdout");
			cnt++;
			if (find_answer_string("stderr", ans) == 1) {
				int index = answer_index;
				answer_index++;
				char temp_file_path[10];
	                        sprintf(temp_file_path, "temp%d", index);
			      	copy_file("complement", temp_file_path);
			} 
		}
		fclose(read_file_ptr);
                if (answer_index > 0) {
                        srand(time(NULL));
                        int rnum = rand() % answer_index;
                        char selected_path[10];
                        sprintf(selected_path, "temp%d", rnum);

                        copy_file(selected_path, "temp");

                        answer_index = 0;
                        stat("temp", &st);
                        file_size = st.st_size;
                        range_size = MIN(file_size, range_size + 1);
                }
	}
	printf("cnt: %d\n",cnt);
}

