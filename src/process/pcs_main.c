#include <stdio.h>
#include <stdlib.h>
#include "../../include/runner.h"
#include "../../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

void
copy_file (char * read_file_path, char * write_file_path) {
	FILE * read_file_ptr = fopen(read_file_path, "r") ;
	FILE * write_file_ptr = fopen(write_file_path, "w+") ;
	struct stat st ;
	stat(read_file_path, &st) ;
	int file_size = st.st_size ;
	write_file (read_file_ptr, write_file_ptr, 0, file_size) ;
	fclose(write_file_ptr) ;
	fclose(read_file_ptr) ;
}

void
write_file (FILE * read_file_ptr, FILE * write_file_ptr, int start, int end) {
	int len = end - start ;
	if (len == 0) {
		return ;
	}

	char buf[1024] ; 
        int div = len / 1024 ;
        int mod = len % 1024 ;
        for (int i = 0 ; i < div ; i++) {
                if (fread(buf, 1024, 1, read_file_ptr) == 1) {
                        fwrite(buf, 1024, 1, write_file_ptr) ;
                }
        }
        if (fread(buf, mod, 1, read_file_ptr) == 1) {
                fwrite(buf, mod, 1, write_file_ptr) ;
        }
}

void
read_file (FILE * read_file_ptr, int start, int end) {
	int len = end - start ;
	if (len == 0) {
		return ;
	}

	char buf[1024] ;
	int div = len / 1024 ;
	int mod = len % 1024 ;
	for (int i = 0 ; i < div ; i++) {
		if (fread(buf, 1024, 1, read_file_ptr) == 0) {
			fprintf(stderr, "read_file function error\n") ;
		}
	}
	if (fread(buf, mod, 1, read_file_ptr) == 0) {
		fprintf(stderr, "read_file function error\n") ;
	}
}

int
main (int argc, char * argv[]) {
	if (argc != 5) {
		fprintf(stderr, "invalid arguments") ;
		exit(EXIT_FAILURE) ;
	}
	if (access(argv[1], X_OK) == -1) {
		perror("main.c argv[1]: ") ;
		exit(errno) ;
	}
	if (access(argv[2], R_OK) == -1) {
		perror("main.c argv[2]: ") ;
		exit(errno) ;
	}
	srand(time(NULL)) ;
	int process_num = atoi(argv[4]) ;

	time_t begin = time(NULL) ;
	for (int i = 0 ; i < process_num ; i++) {
		char temp_path[20] ;
		sprintf(temp_path, "temp%d", i) ;
		copy_file(argv[2], temp_path) ; 
	}
	pcs_range(argv[1], argv[3], process_num) ;
	time_t end = time(NULL) ;
	printf("running time: %ld\n", end - begin) ;
	return 0 ;
}
