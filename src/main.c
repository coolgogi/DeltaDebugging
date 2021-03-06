#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int
main (int argc, char * argv[]) {
	time_t begin = time(NULL);
	if (argc != 7) {
		fprintf(stderr, "invalid arguments\n");
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
		
	ddmin(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]) ;
	time_t end = time(NULL) ;
	printf("running time: %ld\n", end - begin) ;
	return 0;
}
