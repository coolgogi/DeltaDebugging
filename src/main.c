#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main (int argc, char * argv[]) {

	if (argc != 3) {
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
	
	int fp = open("answer", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH) ;
	if (dup2(fp, STDERR_FILENO) == -1) {
        perror("main.c: ") ;    
		exit(errno) ;
    }	
	runner(argv[1], argv[2], "output/ddmin_output.txt") ;
	close(fp) ;	
	printf("result : %s\n", ddmin(argv[1], argv[2])) ;
	return 0;
}
