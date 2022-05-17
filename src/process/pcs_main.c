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
writeFile (FILE * read_file, FILE * write_file, int len, unsigned char * buf) {
        int buf_size = sizeof(&buf) / sizeof(unsigned char) ;
        int div = len / buf_size ;
        int mod = len % buf_size ;
        for (int i = 0 ; i < div ; i ++) {
                if (fread(buf, buf_size, 1, read_file) == 1) {
                        fwrite(buf, buf_size, 1, write_file) ;
                }
        }
        if (fread(buf, mod, 1, read_file) == 1) {
                fwrite(buf, mod, 1, write_file) ;
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

        writeFile(input_file, temp_file, file_size, buf) ;

        fclose(input_file) ;
        fclose(temp_file) ;
        free(buf) ;

	pcs_range(argv[1], temp, argv[3]) ;

        free(temp) ;
	time_t end = time(NULL) ;
	printf("running time: %ld\n", end - begin) ;
	return 0;
}
