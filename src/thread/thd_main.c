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
write_file (FILE * read_file, FILE * write_file, int start, int end) {
	int len = end - start ;
	if (len == 0) {
		return ;
	}
	
	fseek(read_file, start, SEEK_SET);
        char buf[1024];
        int div = len / 1024;
        int mod = len % 1024;
        for (int i = 0; i < div; i++) {
                if (fread(buf, 1024, 1, read_file) == 1) {
                        fwrite(buf, 1024, 1, write_file);
                }
        }
        if (fread(buf, mod, 1, read_file) == 1) {
                fwrite(buf, mod, 1, write_file);
        }
}

int
main (int argc, char * argv[]) {
	time_t begin = time(NULL);
	if (argc != 4) {
		fprintf(stderr, "invalid arguments");
		exit(EXIT_FAILURE);
	}

	if (access(argv[1], X_OK) == -1) {
		perror("main.c argv[1]: ");
		exit(errno);
	}

	if (access(argv[2], R_OK) == -1) {
		perror("main.c argv[2]: ");
		exit(errno);
	}
        struct stat st;
        stat(argv[2], &st) ;
        int file_size = st.st_size ;
        char * temp = (char *) malloc(5) ;
        sprintf(temp, "temp") ;

        FILE * temp_file = fopen(temp, "w+") ;
        FILE * input_file = fopen(argv[2], "r") ;
        unsigned char * buf = (unsigned char *) malloc(1024) ;
        memset(buf, 0, 1024) ;

        write_file(input_file, temp_file, 0, file_size) ;

        fclose(input_file) ;
        fclose(temp_file) ;
        free(buf) ;

	thd_range(argv[1], temp, argv[3]) ;

        free(temp) ;
	time_t end = time(NULL) ;
	printf("running time: %ld\n", end - begin) ;
	return 0;
}
